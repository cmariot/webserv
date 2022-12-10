#include "Webserver.hpp"

int	Webserver::wait_event(int epoll_socket, struct epoll_event *events)
{
	int			nb_ready_fd;
	const int	maxevents = MAX_EVENTS;
	const int	timeout = -1;

	nb_ready_fd = epoll_wait(epoll_socket, events, maxevents, timeout);
	if (nb_ready_fd == -1)
	{
		int err = errno;
		if (err == EINTR)
			return (-2);
		error("epoll_wait() failed.", NULL);
		perror("epoll_wait");
	}
	return (nb_ready_fd);
};
