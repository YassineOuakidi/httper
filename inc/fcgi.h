#ifndef FCGI_H
#define FCGI_H


#include <stdio.h>
#include "./http.h"
#include <arpa/inet.h>


struct FCGI {
	int sockfd;
    	struct sockaddr_in socket_address;
    	socklen_t addr_len;
};

#define php_cgi_exec "/usr/bin/php-cgi"
#define php_address "127.0.0.1:9092"
#define FCGI_PORT 9092
#define php_ip "127.0.0.1"

extern struct FCGI fcgi;

int fcgi_encode_key_value(char **buffer , char *key , size_t key_len , char *value , size_t value_len);


int launch_php_cgi();

int fcgi_init();

int fcgi_connect();

int fcgi_send_request(int fcgi_fd, unsigned short request_id, char **params, int params_count, char *stdin_data, int stdin_length);

void fcgi_send_begin_request();
void fcgi_send_params(char **params , int params_count);
void fcgi_send_stdin(char* stdin_data , int stdin_length);

char *fcgi_read_response(int fcgi_fd, int client_fd);

void fcgi_close_connection(int fcgi_fd);




#endif
