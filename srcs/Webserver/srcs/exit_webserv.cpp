#include "Webserver.hpp"

int	Webserver::exit_webserv(void)
{
	close(epoll_socket);
	for (int i = 0 ; i < nb_events ; ++i)
		close(events[i].data.fd);
	for (size_t i = 0 ; i < nb_of_servers ; ++i)
		close(servers[i].socket);
	for (std::map<int, Client>::iterator it = clients.begin() ; it != clients.end() ; ++it)
		close(it->first);
	close(STDIN);
	close(STDOUT);
	close(STDERR);
	return (1);
};
