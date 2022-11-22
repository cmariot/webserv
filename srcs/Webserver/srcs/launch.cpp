#include "Webserver.hpp"

# define SIGNAL_CAUGHT 1

int		Webserver::launch(char *const *env)
{
	int			client_socket;
	size_t		index;
	Server		request_server;

	if (init_sockets())
		return (exit_webserv());
	catch_signal();
	print(INFO, "Webserv is waiting for clients connexion ...");
	while (true)
	{
		if (wait_event(events, nb_events) == SIGNAL_CAUGHT)
			return (exit_webserv());
		for (size_t i = 0 ; i < nb_events ; ++i)
		{
			if (client_connexion(&index, events[i]))
			{
				accept_connexion(&client_socket, server[index], events);
				// Creer une instance de classe client si client_socket inconnu
				// Sinon ptr sur client
			}
			else
			{
				// Check si on doit fermer socket client dans la requete
				_request.get(events[i].data.fd);
				if (get_server(request_server))
				{
					// send error 404
					remove_client(main_socket, client_socket, events);
					continue ;
				}
				_response.update(_request, request_server, env);
				_response.create(events[i].data.fd);
				//	if (on doit fermer client)
				remove_client(main_socket, client_socket, events);
			}
		}
	}
	return (0);
};
