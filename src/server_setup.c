
#include "../inc/http.h"


void launch_server()
{
	
	if(launch_php_cgi()<0)
	{
		printf("error launching php_cgi");
		exit(EXIT_FAILURE);
	}

	printf("Waiting for PHP-CGI to start...\n");
    	sleep(2);

	//int sockfd = socket(int domain , int type , int protocol);
	serv.socket_fd = socket(AF_INET , SOCK_STREAM , 0);

	
	serv.socket_address.sin_family = AF_INET;
	serv.socket_address.sin_port = htons(PORT);
	serv.socket_address.sin_addr.s_addr = INADDR_ANY;
	serv.addr_len = sizeof(struct sockaddr);	


	int opt = 1;
	
	setsockopt( serv.socket_fd , SOL_SOCKET , SO_REUSEADDR , &opt , sizeof(opt) );


	if(bind(serv.socket_fd ,(struct sockaddr *)&(serv.socket_address) ,serv.addr_len)==-1 )
	{
		close(serv.socket_fd);	
		printf("Error: Error binding the socket\n");
		exit(EXIT_FAILURE);
	}
	
	if(listen(serv.socket_fd , SOMAXCONN)==-1)
	{
		close(serv.socket_fd);
		printf("Error: Error establishing listener\n");
		exit(EXIT_FAILURE);
	}

	printf("Server listenning on port: %d\n\n\n" , PORT);
	
	serv.fcgi_fd = fcgi_init();

	setup_epoll();
}
