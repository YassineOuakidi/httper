

#include "../inc/http.h"


void send_tree(int client_fd , char *url)
{
	
	char *cwd = getenv("PWD");
	if (!cwd)
    	{
        	send_error(client_fd);
        	return;
    	}
	printf("url : %s\n" , url );

    	char *dir_name = ft_strjoin(cwd, url);
    	DIR *dir = opendir(dir_name);
    	if (!dir)
   	{
        	free(dir_name);
        	send_error(client_fd);
        	return;
    	}

    	send_header(client_fd, "Content-Type: text/html\r\n");
    	char buffer[4096];
    	snprintf(buffer, sizeof(buffer),
    	         "<!DOCTYPE html>\n"
    	         "<html><head><title>Directory Listing</title></head><body>\n"
    	         "<h1>Contents of %s</h1><ul>\n", dir_name);
    	write(client_fd, buffer, strlen(buffer));
	
	struct dirent *entry;
	while ((entry = readdir(dir)) != NULL)
    	{

        	char *entry_name  = ft_strdup(entry->d_name);
		char *path_name = ft_strjoin(url , entry_name);
		printf("pathname : %s\n" , path_name);
		if (entry->d_name[0] == '.')
        		continue;
		
		if(entry->d_type == DT_DIR)
			path_name = ft_strjoin(path_name , "/");

        	
		snprintf(buffer, sizeof(buffer),
        	         "<li><a href=\"%s\">%s</a></li>\n",
                	path_name , entry_name);

        	write(client_fd, buffer, strlen(buffer));
    	}
    	snprintf(buffer, sizeof(buffer), "</ul></body></html>\n");

    	write(client_fd, buffer, strlen(buffer));

    	closedir(dir);
    	free(dir_name);
}
void  send_error(int client_fd)
{
	const char *header =
        	"HTTP/1.1 404 OK\r\n"
        	"Content-Type: text/html\r\n"
        	"Connection: close\r\n"
        	"\r\n";
    	write(client_fd, header, strlen(header));
	
	char *error_message = "<html><body><h1> 404 : Not Found </h1></body></html>\n";
	
	write(client_fd , error_message , ft_strlen(error_message));
}
