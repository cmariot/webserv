#include "Webserver.hpp"

static	void connexion_log(const Server & server)
{
	std::string str = "A client try to connect to the server ";
	str += server.get_address().first;
	str += ":";
	str += itostring(server.get_address().second);
	print(INFO, str.c_str());
	return ;
};

bool	Webserver::client_connexion(size_t *server_index, struct epoll_event & event)
{
	for (*server_index = 0 ; *server_index < nb_of_servers ; ++(*server_index))
	{
		if (event.data.fd == server[*server_index]._server_socket)
		{
			connexion_log(server[*server_index]);
			return (true);
		}
	}
	return (false);
};
