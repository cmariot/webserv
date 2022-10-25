#include "Webserver.hpp"

int	Webserver::exit_webserv(int epoll_socket)
{
	close(epoll_socket);
	for (int i = 0 ; i < nb_of_servers ; ++i)
		close(server[i].server_socket);
	close(STDIN);
	close(STDOUT);
	close(STDERR);
	return (0);
};
