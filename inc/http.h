#ifndef HTTP_H
#define HTTP_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include "../libft/libft.h"
#include <sys/epoll.h>
#include <ctype.h>
#include <dirent.h>
#include <signal.h>
#include <sys/sendfile.h>
#include "get_next_line.h"
#include "./fcgi.h"

#define BUFF_SIZE 1024 * 1024
#define PORT 7777
#define MAX_EVENTS 64
#define POST 1
#define GET 0

struct form_data
{
	char* key;
	char* value;
};


struct request
{
	int method;
	char *url;
	int keep_alive;
	int content_len;
	int done;
	char *content_type;
	char *body;
	char *query_string;
	char *host;
	int is_binary;
	char *mime;
	char *cookie;
	struct form_data data[100];
};
struct connection
{
	struct request req;
	int client_fd;
	int state; // 0 read header ,, 1 read body
	int bytes_read;
};

struct server{
	int socket_fd;
	struct sockaddr_in socket_address;
	socklen_t addr_len;
	int epoll_fd;
	int fcgi_fd;
	int php_cgi_pid;
	int php_cgi_port;
};

extern struct server serv;

void set_nonblocking(int fd);

void launch_server();

void setup_epoll();

int process_req(int client_fd);
char *read_req(int client_fd);
struct request parse_req(char *buff);
void parse_body(char *buffer , struct request *req);
void process_formdata(struct request **req);
void process_urlencoded(struct request **req);
void process_json(struct request **req);

void response(int client_fd , struct request req);
void send_template(int client_fd);
void send_error(int client_fd);
void send_tree(int client_fd , char *url);
void send_header(int client_fd , char *mime);
void handle_php(int client_fd , struct request req);


void free_mat(char **mat);
#endif
