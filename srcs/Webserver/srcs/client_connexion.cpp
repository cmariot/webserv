#include "Webserver.hpp"

bool	Webserver::client_connexion(ssize_t *server_index, struct epoll_event & event)
{
	for (*server_index = 0 ; *server_index < nb_of_servers ; ++(*server_index))
		if (event.data.fd == server[*server_index].server_socket)
			return (true);
	return (false);
};