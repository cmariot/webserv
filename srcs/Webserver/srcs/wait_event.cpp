#include "Webserver.hpp"

int		Webserver::wait_event(void)
{
	nb_events = epoll_wait(main_socket, events, MAX_EVENTS, -1);
	if (nb_events == -1)
	{
		if (errno == EINTR)
			return (1);
		std::cerr << "epoll_wait" << std::endl;
	}
	return (0);
};

