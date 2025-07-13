

#include "../inc/fcgi.h"


int launch_php_cgi()
{
	serv.php_cgi_pid = fork();

	if(serv.php_cgi_pid<0)
	{
		printf("Error fork()\n");
		return -1;
	}
	if(serv.php_cgi_pid==0)
	{
		execl( php_cgi_exec , "php-cgi", "-b" , php_address , (char *)NULL);
	}
	return 0;
}
