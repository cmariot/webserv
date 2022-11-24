#include "Webserver.hpp"

int	Webserver::exit_webserv(void)
{
	close(epoll_socket);
	for (size_t i = 0 ; i < nb_of_servers ; ++i)
		close(server[i].socket);
	for (int i = 0 ; i < nb_events ; ++i)
		close(events[i].data.fd);
	close(STDIN);
	close(STDOUT);
	close(STDERR);
	return (1);
};
