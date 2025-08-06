
#include "./inc/http.h"

struct server serv;

int main()
{
	signal(SIGPIPE, SIG_IGN);
	
	launch_server();
	exit(EXIT_FAILURE);
}
