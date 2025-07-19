

#include "../inc/fcgi.h"

int last = 0;


int fcgi_encode_key_value(char **buffer, char *key, size_t key_len, char *value, size_t value_len)
{
	size_t total_len = 0;
	unsigned char *buf = malloc( key_len + value_len + 8 ); 

	if (key_len < 128) {
		buf[total_len++] = key_len;
	} else {
		buf[total_len++] = (key_len >> 24) | 0x80;
		buf[total_len++] = (key_len >> 16) & 0xFF;
		buf[total_len++] = (key_len >> 8) & 0xFF;
		buf[total_len++] = key_len & 0xFF;
	}

	if (value_len < 128) {
		buf[total_len++] = value_len;
	} else {
		buf[total_len++] = (value_len >> 24) | 0x80;
		buf[total_len++] = (value_len >> 16) & 0xFF;
		buf[total_len++] = (value_len >> 8) & 0xFF;
		buf[total_len++] = value_len & 0xFF;
	}

	memcpy(buf + total_len, key, key_len);
	total_len += key_len;
	memcpy(buf + total_len, value, value_len);
	total_len += value_len;
	*buffer = (char *)buf;
	return total_len;
}
void fcgi_send_begin_request()
{
	unsigned char fcgi_begin_request[16] = {
		1, 1,          // version = 1, type = 1 (FCGI_BEGIN_REQUEST)
    		0, 1,          // requestId = 1 (0x0001)
    		0, 8,          // contentLength = 8
    		0, 0,          // paddingLength = 0, reserved
    		0, 1,          // role = 1 (FCGI_RESPONDER)
    		1,             // flags = 0 (close connection) flags = 1 (keep alive)
    		0, 0, 0, 0, 0  // reserved[5]
	};
	
	send(serv.fcgi_fd , fcgi_begin_request , 16 , 0);

}

void fcgi_send_params(char **params , int params_count)
{
	unsigned char fcgi_params_header[8] = {
		1 , 4,
		0 , 1,
		0 , 0,
		0,
		0
	};
	char *buffer = NULL;
	size_t		i = 0;

	printf("\n\n\n====================params===================\n");

	while(params[i])
	{
		printf("%s , %s\n" , params[i] , params[i+1]);
		size_t content_len = fcgi_encode_key_value(&buffer , params[i] , ft_strlen(params[i]) , params[i+1] , ft_strlen(params[i+1]));

		fcgi_params_header[4] = (content_len >> 8) & 0xFF;
		fcgi_params_header[5] = content_len & 0xFF;

		if(content_len>0)
		{
			send(serv.fcgi_fd , fcgi_params_header , 8 , 0);
			send(serv.fcgi_fd , buffer , content_len , 0 );
		}
		free(buffer);
		i+=2;
	}
	unsigned char empty_params[8] = {
        	1, 4,   // version, type
        	0, 1,   // requestId
        	0, 0,   // contentLength = 0
        	0,      // paddingLength
        	0       // reserved
    	};
    	send(serv.fcgi_fd, empty_params, 8, 0);
}

void fcgi_send_stdin(char *stdin_data , int stdin_length)
{
	unsigned char fcgi_stdin_header[8] = {
    		1, 5,          // version = 1, type = 5 (FCGI_STDIN)
    		0, 1,          // requestId = 1
    		0, 0,          // contentLength = filled dynamically
    		0,             // paddingLength = optional
    		0              // reserved
	};
	fcgi_stdin_header[4] = (stdin_length >> 8) & 0xFF;
	fcgi_stdin_header[5] = stdin_length & 0xFF;
	
	send(serv.fcgi_fd , fcgi_stdin_header , 8 , 0);

	send(serv.fcgi_fd , stdin_data , stdin_length , 0);
	
	fcgi_stdin_header[4] = 0;

	fcgi_stdin_header[5] = 0;

	send(serv.fcgi_fd , fcgi_stdin_header , 8 , 0);

}
















