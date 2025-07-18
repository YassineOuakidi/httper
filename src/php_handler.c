

#include "../inc/http.h"


char *polish(char *s)
{
	char *answer = ft_strdup(s);
	size_t		i = ft_strlen(s) - 1;
	while(answer[i]=='\r' || answer[i] == '\n')
	{
		answer[i] = '\0';
		i--;
	}
	return answer;
}



size_t send_header_get_padding(int client_fd , char *resp)
{
	char **resp_splited = ft_split(resp , '\n');
	size_t 		i = 0;
	size_t		padding = 9;
	while(strcmp(resp_splited[i] , "\r")!=0 )
	{
		padding+= ft_strlen(resp_splited[i] + 1);
		i++;
	}
	i++;
	send_header(client_fd , "Content-Type : text/html\r\n");
	padding+=ft_strlen(resp_splited[i]);

	return padding;
}


void send_resp(int client_fd, char *resp)
{
	char status[64] = "200 OK";
	char *header_end = strstr(resp, "\r\n\r\n");
	if (!header_end)
		header_end = strstr(resp, "\n\n"); 

	if (!header_end) {
		write(client_fd, "HTTP/1.1 500 Internal Server Error\r\nConnection: close\r\n\r\n", 56);
		return;
	}

	size_t header_len = header_end - resp;
	char headers[2048];
	strncpy(headers, resp, header_len);
	headers[header_len] = '\0';

	char *status_line = strstr(headers, "Status:");
	if (status_line) {
		status_line += 7;
		while (*status_line == ' ') status_line++; 
		sscanf(status_line, "%63[^\r\n]", status);
	}

	char *current_header = headers;
	char *set_cookie_header;
	char cookie_buffer[2048];
	cookie_buffer[0] = '\0';

	while ((set_cookie_header = strstr(current_header, "Set-Cookie:")) != NULL) {
		char *end_of_line = strstr(set_cookie_header, "\r\n");
		if (!end_of_line) {
			end_of_line = strstr(set_cookie_header, "\n");
		}
		if (end_of_line) {
			strncat(cookie_buffer, set_cookie_header, end_of_line - set_cookie_header + 2); 
			current_header = end_of_line + 2; 
		} else {
			strcat(cookie_buffer, set_cookie_header);
			break;
		}
	}
	// Send HTTP status line and headers (including cookies)

	printf("============header===============\nHTTP/1.1 %s\r\n%s%s\r\n\r\n", status, headers, cookie_buffer);
	dprintf(client_fd, "HTTP/1.1 %s\r\n%s%s\r\n\r\n", status, headers, cookie_buffer);
	char *body = header_end + ((header_end[1] == '\n') ? 2 : 4);
	write(client_fd, body, strlen(body));

	printf("\n\n\n==============resp================\n%s=============================" , body);
}

void handle_php(int client_fd , struct request req)
{

	char buf_gateway[16];
    	char buf_request_method[8];
    	char *buf_script_filename;
    	char buf_query_string[1024];
    	char buf_server_protocol[16];
	char buf_content_len[16];
	char buf_content_type[128];
	char buf_cookie[128];

    	snprintf(buf_gateway, sizeof(buf_gateway), "%s", "FastCGI/1.0");
    	snprintf(buf_request_method, sizeof(buf_request_method),  "%s",req.method == POST ? "POST" : "GET");
    	snprintf(buf_query_string, sizeof(buf_query_string), "%s", req.query_string ? req.query_string : NULL);

	char *tmp_cookie;
	if(req.cookie)
		tmp_cookie = polish(req.cookie);

	snprintf(buf_cookie , sizeof(buf_cookie) , "%s" , req.cookie ? tmp_cookie : NULL);
	if(req.cookie)
		free(tmp_cookie);

    	snprintf(buf_server_protocol, sizeof(buf_server_protocol), "%s", "HTTP/1.1");

	char *tmp_len = ft_itoa(req.content_len);
	snprintf(buf_content_len , sizeof(buf_content_len) , "%s" , tmp_len);
	free(tmp_len);

	if(req.content_type)
		snprintf(buf_content_type , sizeof(buf_content_type) , "%s" , req.content_type ? polish(req.content_type) : NULL);
	printf("here2\n");
	char *docroot = ft_strjoin( getenv("PWD") , "/templates");


	buf_script_filename = ft_strjoin(docroot , req.url);
	char *params[17] ;
	int index = 0;
	params[index++] = "GATEWAY_INTERFACE";
	params[index++] = "FastCGI/1.0";
	params[index++] = "REQUEST_METHOD";
	params[index++] = req.method == POST ? "POST" : "GET";
	params[index++] = "SCRIPT_FILENAME";
	params[index++] = buf_script_filename;
	if( req.query_string)
	{
		params[index++] = "QUERY_STRING";
		params[index++] = buf_query_string;
	}
	params[index++] = "SERVER_PROTOCOL";
	params[index++] = "HTTP/1.1";
	if(req.content_len>0)
	{
		params[index++] = "CONTENT_LENGTH";
		params[index++] = buf_content_len;
		params[index++] = "CONTENT_TYPE";
		params[index++] = buf_content_type;
	}
	if(req.cookie)
	{
		params[index++] = "HTTP_COOKIE";
		params[index++] = buf_cookie;
	}
	params[index++] = NULL;

	int params_count = sizeof(params) / sizeof(params[0]);
	
		
	size_t 	i = 0;

	fcgi_send_request(serv.fcgi_fd , 1 , params , params_count , req.body , req.content_len);
	
	char *resp = fcgi_read_response(serv.fcgi_fd , client_fd);
	
	send_resp(client_fd , resp);
	
}
