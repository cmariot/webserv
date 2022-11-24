#include "Webserver.hpp"

int	Webserver::exit_webserv(void)
{
	close(epoll_socket);
	for (size_t i = 0 ; i < nb_of_servers ; ++i)
		close(server[i].socket);
	close(STDIN);
	close(STDOUT);
	close(STDERR);
	return (1);
};
