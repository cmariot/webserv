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
				_request.get_client_request(events[i].data.fd);
				_request.interpret();
				get_server(request_server);
				_response.update(_request, request_server);
				_response.send_response(events[i].data.fd);
				if (remove_client(epoll_socket, client_socket, events))
					return (exit_webserv());
			}
		}
	}
	return (0);
};

