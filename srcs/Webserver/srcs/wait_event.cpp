#include "Webserver.hpp"

int	Webserver::wait_event(struct epoll_event *events, size_t & nb_events)
{
	int			nb_ready_fd;
	const int	maxevents = MAX_EVENTS;
	const int	timeout = -1;
	int			err;

	nb_ready_fd = epoll_wait(epoll_socket, events, maxevents, timeout);
	if (nb_ready_fd == -1)
	{
		err = errno;
		if (err == EINTR) // Signal caught
			return (1);
		error("wait events");
	}
	nb_events = nb_ready_fd;
	return (0);
};
