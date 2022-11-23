#include "Webserver.hpp"

bool	Webserver::client_connexion(size_t & server_index, struct epoll_event & event)
{
	std::cout << "Event fd = " <<  event.data.fd << std::endl;
	for (server_index = 0 ; server_index < nb_of_servers ; ++server_index)
	{
		std::cout << "Server socket = " <<  server[server_index].socket << std::endl;
		if (event.data.fd == server[server_index].socket)
		{
			return (true);
		}
	}
	return (false);
};

int		Webserver::launch(char *const *env)
{
	(void)env;
	// Ouvrir un epoll_socket avec epoll create
	main_socket = epoll_create1(0);

	// Pour chaque serveur : 
	for (size_t i = 0 ; i < nb_of_servers ; ++i)
	{
		// Ouvrir un socket
		server[i].socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (server[i].socket == -1)
			std::cerr << "socket" << std::endl;

		//setsockopt ?

		// Attribuer un type, un host et un port a l'addresse de ce socket
		server[i].address.sin_family = AF_INET;
		server[i].address.sin_addr.s_addr = inet_addr(server[i].get_address().first.c_str());
		server[i].address.sin_port = htons(server[i].get_address().second);

		// Bind socket et addresse
		if (bind(server[i].socket, (const sockaddr *)&server[i].address, sizeof(server[i].address)) == -1)
			std::cerr << "bind" << std::endl;

		// Listen
		if (listen(server[i].socket, 100) == -1)
			std::cerr << "listen" << std::endl;

		// Options du server_socket
		bzero(&event, sizeof(event));
		event.data.fd = server[i].socket;
		event.data.ptr = &server[i];
		event.events = EPOLLIN | EPOLLOUT | EPOLLRDHUP;

		// Non-blocking socket
		//if (fcntl(server[i].socket, F_SETFL, O_NONBLOCK) == -1)
		//	std::cerr << "fcntl" << std::endl;

		// Ajout a la liste d'interet
		if (epoll_ctl(main_socket, EPOLL_CTL_ADD, server[i].socket, &event) == -1)
			std::cerr << "epoll_ctl" << std::endl;
	}

	size_t	server_index = 0;
	// Signal catcher
	while (1)
	{
		nb_events = epoll_wait(main_socket, events, MAX_EVENTS, -1);	
		if (nb_events == -1)
		{
			std::cerr << "epoll_wait" << std::endl;
			break ;
		}
		for (int i = 0 ; i < nb_events ; ++i)
		{
			if (client_connexion(server_index, events[i]))
			{
				std::cout << _server.get_host() << std::endl;
				return (0);
			}
			else
				return (1);

			std::cout << server_index << std::endl;
		}
	}

	// Close
	exit_webserv();

	return (0);
};
