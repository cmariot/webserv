#include "Webserver.hpp"

#define SIGNAL_CAUGHT nb_events == -2

bool	Webserver::new_client_connexion(ssize_t *server_index, struct epoll_event & event)
{
	for (*server_index = 0 ; *server_index < nb_of_servers ; ++(*server_index))
		if (event.data.fd == server[*server_index].server_socket)
			return (true);
	return (false);
};

int		Webserver::init_sockets(void)
{
	if (create_epoll_socket(&epoll_socket))
		return (1);
	for (int i = 0 ; i < nb_of_servers ; ++i)
	{
		if (server[i].create_server_socket())
			return (1);
		if (server[i].bind_server_address())
			return (1);
		if (server[i].listen_for_clients())
			return (1);
		if (add_to_interest_list(&server[i], epoll_socket))
			return (1);
		std::cout << "Server " << server[i].server_socket << " is listening on " << server[i].ip << ":" << server[i].port << std::endl;
	}
	return (0);
};

int		Webserver::launch(void)
{
	ssize_t				nb_events;
	struct epoll_event	events[MAX_EVENTS];
	int					client_socket;
	ssize_t				index;
	
	if (init_sockets())
		return (exit_webserv());
	catch_signal();
	std::cout << "Waiting for new events ..." << std::endl;
	while (true)
	{
		nb_events = wait_event(epoll_socket, events);
		if (SIGNAL_CAUGHT || nb_events == -1)
			return (exit_webserv());
		for (ssize_t i = 0 ; i < nb_events ; ++i)
		{
			if (new_client_connexion(&index, events[i]))
			{
				std::cout << "A client has just connected to the server " << server[index].ip << ":" << server[index].port << std::endl;
				if (accept_connexion(server[index].server_socket, server[index].server_address, &client_socket))
					return (exit_webserv());
				if (add_client(epoll_socket, client_socket, events))
					return (exit_webserv());
			}
			// else if client disconnect
			//		remove client
			else
			{
				//std::cout << "Event traitment" << std::endl;
				char request[1024];
				memset(request, 0, 1024);
				recv(events[i].data.fd, request, 1024, 0);
				std::cout << request;

				char response[1024];
				strcpy(response, "Response : OK\n");
				send(events[i].data.fd, response, strlen(response), 0);

				if (remove_client(epoll_socket, client_socket, events))
					return (exit_webserv());
			}
		}
	}
	return (0);
};
