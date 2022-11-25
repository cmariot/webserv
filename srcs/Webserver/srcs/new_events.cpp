#include "Webserver.hpp"

int		Webserver::new_events(void)
{
	nb_events = epoll_wait(epoll_socket, events, MAX_EVENTS, -1);
	if (nb_events == -1)
	{
		if (errno == EINTR)
			return (false);
		else
			error("epoll_wait");
	}
	return (true);
};

