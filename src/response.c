

#include "../inc/http.h"

void send_header(int client_fd, char *mime)
{
	char header[256];
	snprintf(header, sizeof(header),
		"HTTP/1.1 200 OK\r\n"
		"%s"
		"Connection: close\r\n"
		"\r\n",
		mime 
	);
	write(client_fd, header, strlen(header));
}


void get_resp(int client_fd , struct request req)
{
	if(strcmp(req.mime , "Content-Type: application/x-httpd-php\r\n")==0)
	{
		handle_php(client_fd , req);
		return;
	}
	char *url = ft_strjoin("/templates" , req.url);
	int tmp_fd = open(url + 1 , O_RDONLY );
	printf("tmp_fd : %d\n" , tmp_fd);
	if(tmp_fd == -1 || *(url + ft_strlen(url) - 1) =='/')
	{
		close(tmp_fd);
		send_tree(client_fd , url);
		return ;
	}
	send_header(client_fd , req.mime);
	char *write_buffer = malloc(1024);
	ssize_t bytes_read = 0;

	while((bytes_read = read(tmp_fd , write_buffer , 1024)) > 0 )
	{
		write(client_fd , write_buffer , bytes_read);
		free(write_buffer);
		write_buffer = malloc(1024);
	}
	free(write_buffer);
}

void post_resp(int client_fd , struct request req)
{
	get_resp(client_fd , req);
}

void response(int client_fd , struct request req)
{
	if(req.method == GET)
		get_resp(client_fd , req);
	else
		post_resp(client_fd , req);
}
