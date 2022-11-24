#include "Webserver.hpp"

int		Webserver::new_events(void)
{
	//std::cout << "Waiting new events ..." << std::endl;
	nb_events = epoll_wait(epoll_socket, events, MAX_EVENTS, -1);
	if (nb_events == -1)
	{
		if (errno == EINTR)
		{
			signal = true;
			return (false);
		}
		std::cerr << "epoll_wait" << std::endl;
	}
	return (true);
};

