
#include "../inc/http.h"


void set_nonblocking(int fd)
{
	int flags = fcntl(fd , F_GETFL , 0);
	if(flags==-1)
		return ;
	fcntl(fd , F_SETFL , flags | O_NONBLOCK);
}


void setup_epoll()
{
	set_nonblocking(serv.socket_fd);
	int epoll_fd , client_fd , ntfds;
	struct epoll_event ev , events[MAX_EVENTS];
	
	epoll_fd = epoll_create(100);
	if( epoll_fd == -1)
	{
		close(serv.socket_fd);
		printf("Error: Error epoll\n");
		exit(EXIT_FAILURE);
	}
	
	ev.events = EPOLLIN;
	ev.data.fd = serv.socket_fd;
	
	if(epoll_ctl(epoll_fd , EPOLL_CTL_ADD , serv.socket_fd , &ev) == -1 )
	{
		printf("Error: Error epoll_ctl\n");
		close(serv.socket_fd);
		close(epoll_fd);
		exit(EXIT_FAILURE);
	}

	serv.epoll_fd = epoll_fd;

	while(1)
	{
		ntfds = epoll_wait(serv.epoll_fd , events , MAX_EVENTS , -1);
		
		for(int i = 0 ; i < ntfds ; i++)
		{

			if(events[i].data.fd == serv.socket_fd)
			{
				client_fd = accept(serv.socket_fd , (struct sockaddr*)&serv.socket_address , &(serv.addr_len));
				set_nonblocking(client_fd); 
				
				//adding new client  to epoll
				
				ev.events = EPOLLIN;
				ev.data.fd = client_fd;
				
				if(epoll_ctl(serv.epoll_fd , EPOLL_CTL_ADD , client_fd , &ev)==-1)
					continue;
			}

			else
			{
				int fd_tmp = events[i].data.fd;
				int keep_alive = process_req(events[i].data.fd);
				epoll_ctl(serv.epoll_fd , EPOLL_CTL_DEL , events[i].data.fd , NULL);
				close(fd_tmp);
				
			}
		}
		
	}	
	
}
