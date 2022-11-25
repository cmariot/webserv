#include "Webserver.hpp"

size_t Webserver::nb_of_servers = 0;

Webserver::Webserver(void) :
	nb_events(0),
	_env(NULL)
{
	bzero(buffer, BUFFER_SIZE);
	bzero(events, sizeof(struct epoll_event) * MAX_EVENTS);
	return ;
};
