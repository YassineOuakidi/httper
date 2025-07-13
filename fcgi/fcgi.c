

#include "../inc/fcgi.h"

struct FCGI fcgi;

int fcgi_init()
{
    	fcgi.sockfd = socket(AF_INET, SOCK_STREAM, 0);
    	if (fcgi.sockfd < 0) {
    	    perror("fcgi_init: socket creation failed\n");
    	    exit(EXIT_FAILURE);
    	}
	int connection = fcgi_connect();
    	return fcgi.sockfd;
}


int fcgi_connect()
{
	fcgi.socket_address.sin_family = AF_INET;
	fcgi.socket_address.sin_port = htons(FCGI_PORT);
	fcgi.socket_address.sin_addr.s_addr = inet_addr(php_ip);
	fcgi.addr_len = sizeof(struct sockaddr);

	if(connect(fcgi.sockfd , (struct sockaddr *)&(fcgi.socket_address) , fcgi.addr_len ) < 0)
	{
		perror("fcgi_connect: socket connection failed\n");
		close(fcgi.sockfd);
	}
	else 
		printf("FCGI listenning on port: %d\n" , FCGI_PORT);
	return 0;
}

int fcgi_send_request(int fcgi_fd , unsigned short request_id , char **params , int params_count, char *stdin_data , int stdin_length)
{
	printf("sending begin_request...\n");
	fcgi_send_begin_request();
	printf("sending params...\n");
	fcgi_send_params(params , params_count);
	printf("sending data...\n");
	if( stdin_length > 0)
	{
		fcgi_send_stdin(stdin_data , stdin_length);
	}
	printf("ending\n");
}

char *fcgi_read_response(int fcgi_fd, int client_fd) {
    	char *response = NULL;
    	size_t total_size = 0;

    	while (1) {
        	
		unsigned char header[8];
        	ssize_t n = read(fcgi_fd, header, 8);
        	if (n <= 0) break;

        	int type = header[1];
        	int requestId = (header[2] << 8) | header[3];
        	int contentLength = (header[4] << 8) | header[5];
        	int paddingLength = header[6];
	
        	char *content = malloc(contentLength);
        	read(fcgi_fd, content, contentLength);
        
        	if (paddingLength > 0) {
            		char skip[paddingLength];
            		read(fcgi_fd, skip, paddingLength);
        	}

        	if (type == 6 && contentLength > 0) {
            		response = realloc(response, total_size + contentLength + 1);
            		memcpy(response + total_size, content, contentLength);
            		total_size += contentLength;
            		response[total_size] = '\0';
        	}

        	free(content);

        	if ((type == 6 && contentLength == 0) || type == 3 )
            		break;
    	}

    	return response;
}
