#include "Webserver.hpp"

# define SIGNAL_CAUGHT 1

int		Webserver::launch(void)
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
				accept_connexion(&client_socket, server[index], events);
			else
			{
				_request.get(events[i].data.fd);
				get_server(request_server);
				// _response.update(_request, request_server);
				// _response.create(events[i].data.fd);
				// remove_client(main_socket, client_socket, events);
			}
		}
	}
	return (0);
};
