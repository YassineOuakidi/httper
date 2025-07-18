

#include "../inc/http.h"


void parse_body(char *buffer , struct request *req)
{
	req->body = malloc(req->content_len + 1);
	if(!req->body)
		return;
	memmove( req->body , buffer + ft_strlen(buffer) - req->content_len  , req->content_len);
}

struct request init_req()
{
	struct request req = {
		.method = -1,
		.url = NULL,
		.keep_alive = 0,
		.content_len = 0,
		.content_type = NULL,
		.body = NULL,
		.query_string = NULL,
		.host = NULL,
		.mime = NULL,
		.cookie = NULL,
	};
	return req;
}


void get_method_url_querystr(struct request *req , char *str)
{
	char **splited = ft_split(str , ' ');
	req->method = (strcmp(splited[0] , "POST")==0) ? POST : GET;
	char **url_splited = ft_split(splited[1] , '?');
	
	if(url_splited[0][ft_strlen("/templates")] && strncmp("/templates" , url_splited[0] , ft_strlen("/templates")) == 0)
		req->url = ft_strdup(url_splited[0]) + ft_strlen("/templates");
	else
		req->url = ft_strdup(url_splited[0]);

	size_t i=1;
	while(url_splited[i])
	{
		char *tmp_join = ft_strdup(req->query_string);
		free(req->query_string);
		req->query_string = ft_strjoin(tmp_join , url_splited[i]);
		free(tmp_join);
		i++;
	}
	free_mat(splited);
	free_mat(url_splited);
}

void get_content_len(struct request *req , char *str)
{
	req->content_len = atoi(str + ft_strlen("Content-lenght:"));
}

void get_content_type(struct request *req , char *str)
{
	req->content_type = ft_strdup(str + ft_strlen("Content-type: "));
}

void get_cookie(struct request *req , char *str)
{
	req->cookie = ft_strdup(str + ft_strlen("Cookie: "));
}

void get_host(struct request *req , char *str)
{
	req->host = ft_strdup(str + ft_strlen("Host:"));
}

void get_mime_type(struct request *req, char *url)
{
	const char *type;

	if( strstr(url , ".php"))
		type = "application/x-httpd-php";
	else if (strstr(url, ".html"))
		type = "text/html";
	else if (strstr(url, ".css"))
		type = "text/css";
	else if (strstr(url, ".js"))
		type = "application/javascript";
	else if (strstr(url, ".png"))
		type = "image/png";
	else if (strstr(url, ".jpg") || strstr(url, ".jpeg"))
		type = "image/jpeg";
	else if (strstr(url, ".gif"))
		type = "image/gif";
	else if (strstr(url, ".svg"))
		type = "image/svg+xml";
	else if (strstr(url, ".ico"))
		type = "image/x-icon";
	else
		type = "application/octet-stream";

	char buffer[128];
	snprintf(buffer, sizeof(buffer), "Content-Type: %s\r\n", type);
	req->mime = ft_strdup(buffer);

}

struct request parse_req(char *buff)
{
	size_t 		j = 0 , i = 0;
	char **splited = ft_split(buff , '\n');
	
	struct request req = init_req();
	
	while(splited[i] && strcmp(splited[i] , "\r")!=0) 
	{
		j+=ft_strlen(splited[i]);
		if(i == 0)
			get_method_url_querystr(&req , splited[i]);
		else if(strncmp("Content-Length:" , splited[i] , ft_strlen("content-length:")) == 0)
			get_content_len(&req , splited[i]);
		else if(strncmp("Content-Type:" , splited[i] , ft_strlen("content-type:")) == 0)
			get_content_type(&req , splited[i]);
		else if(strncmp("Host:" , splited[i] , ft_strlen("Host:"))==0)
			get_host(&req , splited[i]);
		else if(strcmp("Connection: keep-alive\r" , splited[i])==0)
			req.keep_alive = 1;
		else if(strncmp("Cookie: " , splited[i] , ft_strlen("Cookie: "))==0)
			get_cookie(&req , splited[i]);
		i++;
		
	}
	
	if(!req.query_string)
	{
		printf("query string is  null \n");
	}
	get_mime_type(&req , req.url);
	
	return req;
}
