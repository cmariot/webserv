#include "Webserver.hpp"

#define SIGNAL_CAUGHT nb_events == -2

int		Webserver::launch(void)
{
	int			client_socket;
	ssize_t		index;
	
	if (init_sockets())
		return (exit_webserv());
	catch_signal();
	while (true)
	{
		nb_events = wait_event(events);
		if (SIGNAL_CAUGHT || nb_events == -1)
			return (exit_webserv());
		for (ssize_t i = 0 ; i < nb_events ; ++i)
		{
			if (client_connexion(&index, events[i]))
			{
				std::cout << "A client has just connected to the server " << server[index].get_address().first << ":" << server[index].get_address().second << std::endl;
				if (accept_connexion(&client_socket, server[index]))
					return (exit_webserv());
				if (add_client(client_socket, events))
					return (exit_webserv());
			}
			else
			{
				// Obtenir la requete du client
				_request.get_client_request(events[i].data.fd);
				std::cout << _request.request << std::endl;
				// Parser la requete pour trouver le serveur qui va etre utilise pour repondre
				// Envoyer la reponse au client

				if (server_response(events[i].data.fd, (char *)_request.request.c_str())) // invalid read
				{
					std::cout << "response failure" << std::endl;
					return (exit_webserv());
				}

				if (remove_client(epoll_socket, client_socket, events))
					return (exit_webserv());
			}
		}
	}
	return (0);
};
