
#include "../inc/http.h"

void print_request(struct request req)
{
	printf("=== HTTP Request ===\n");
	printf("Method       : %s\n", req.method == POST ? "POST" : "GET");
	printf("URL          : %s\n", req.url ? req.url : "(null)");
	printf("Query String : %s\n", req.query_string ? req.query_string : "(null)");
	printf("Host         : %s\n", req.host ? req.host : "(null)");
	printf("Content-Type : %s\n", req.content_type ? req.content_type : "(null)");
	printf("Content-Length: %d\n", req.content_len);
	printf("Body: %s\n", req.body ? req.body : "(null)" ) ;
	
	int i = 0;
	while(req.data[i].key)
	{
		printf("key   : %s | value   :  %s\n" , req.data[i].key , req.data[i].value);
		i++;
	}
	printf("====================\n\n");
}

void process_body(struct request *req)
{
	if(strncmp(req->content_type , "multipart/form-data;" , ft_strlen("multipart/form-data;")) == 0)
		process_formdata(&req);
	else if(strncmp(req->content_type , "application/x-www-form-urlencoded" , ft_strlen("application/x-www-form-urlencoded") ) == 0)
		process_urlencoded(&req);
}

int process_req(int client_fd)
{
	
	char *req_buffer = read_req(client_fd);
	
	if(!req_buffer)
		return 0;
	
	struct request req = parse_req(client_fd , req_buffer);

	char *query_string_decoded = decode(req.query_string);

	free(req.query_string);

	req.query_string = ft_strdup(query_string_decoded);

	printf("query string decoded : %s\n" , query_string_decoded);

	free(query_string_decoded);
	
	if(req.content_len>0)
	{
		parse_body(req_buffer , &req);
		process_body(&req);
	}

	print_request(req);
	
	int secured = secure(req);

	printf("security check : %d\n" , secured);

	if(secured == 0)
	{
		send_error(client_fd);
		return 0;
	}

	free(req_buffer);
	
	response(client_fd , req);
	return 1;
}
