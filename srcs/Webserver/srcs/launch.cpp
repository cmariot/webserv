#include "Webserver.hpp"

# define SIGNAL_CAUGHT 1

int		Webserver::launch(char *const *env)
{
	int			client_socket;
	size_t		index;
	Server		request_server;

	(void)env;
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
				std::cout << "Client connexion !" << std::endl;
			}
			else
			{
				char	buffer[10];
				int		recv_return = 10;

				print(INFO, "Getting the client's request");
				
				_request.request.clear();
				bzero(buffer, 10);
				recv_return = recv(client_socket, buffer, 9, 0);
				if (recv_return <= 0)
				{
					remove_client(main_socket, client_socket, events);
					return (0);
				}
				std::cout << _request.request << std::endl;
			}
		}
	}
	return (0);
};
