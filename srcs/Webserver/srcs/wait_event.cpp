#include "Webserver.hpp"

#define SIGNAL_CAUGHT 1

static	void wait_event_log(int nb_events)
{
	std::string str = itostring(nb_events);
	if (nb_events == 1)
	{
		str += " event to treat.";
		print(INFO, str.c_str()); 
	}
	else if (nb_events > 1)
	{
		str += " events to treat.";
		print(INFO, str.c_str()); 
	}
	return ;
};

int	Webserver::wait_event(struct epoll_event *events, size_t & nb_events)
{
	int			nb_ready_fd;
	const int	maxevents = MAX_EVENTS;
	const int	timeout = -1;

	nb_ready_fd = epoll_wait(main_socket, events, maxevents, timeout);
	if (nb_ready_fd == -1 && errno == EINTR)
		return (SIGNAL_CAUGHT);
	else if (nb_ready_fd == -1)
		error("wait events error");
	nb_events = nb_ready_fd;
	wait_event_log(nb_events);
	return (0);
};
