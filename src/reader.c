
#include "../inc/http.h"


int get_data_len(char *str)
{
	char **splited = ft_split(str , ':');
	int len = atoi(splited[1]);
	free(splited[0]);
	free(splited[1]);
	free(splited);
	return len;

}


char *read_req(int client_fd)
{
	char * buffer = malloc( BUFF_SIZE );
	
	read(client_fd , buffer , BUFF_SIZE );
	printf("=============header==============\n%s=============================" , buffer);
	return buffer;
}
