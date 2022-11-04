#include "Webserver.hpp"

int		Webserver::init_sockets(void)
{
	if (create_epoll_socket())
		return (1);
	for (int i = 0 ; i < nb_of_servers ; ++i)
	{
		if (server[i].create_server_socket())
			return (1);
		if (server[i].bind_server_address())
			return (1);
		if (server[i].listen_for_clients())
			return (1);
		if (add_to_interest_list(&server[i]))
			return (1);
		std::cout << "Server " << server[i]._server_socket << " is listening on " << server[i].get_address().first << ":" << server[i].get_address().second << std::endl;
	}
	return (0);
};
