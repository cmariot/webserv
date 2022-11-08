#include "Webserver.hpp"

#define SIGNAL_CAUGHT nb_events == -2

int		Webserver::launch(void)
{
	int			client_socket;
	ssize_t		index;
	Server		request_server;

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

				// Parser la requete pour trouver les informations utiles pour la reponse
				_request.interpret();

				// Determiner a quel serveur on va envoyer la reponse :
				// On a l'host de la requete, il faut le faire correpondre a un seveur via la directive listen et/ou server_names
				get_server(request_server);
				// Envoyer la reponse au client
				_response.send_response(events[i].data.fd, _request);
				// if (_(events[i].data.fd, (char *)_request.request.c_str()))
				// {
				// 	std::cout << "response failure" << std::endl;
				// 	return (exit_webserv());
				// }
				cout << "response sent" << endl;

				if (remove_client(epoll_socket, client_socket, events))
					return (exit_webserv());
			}
		}
	}
	return (0);
};

