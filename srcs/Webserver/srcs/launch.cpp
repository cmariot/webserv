#include "Webserver.hpp"

int	Webserver::remove_client(int epoll_socket, int client_socket, struct epoll_event *server_event)
{
	epoll_ctl(epoll_socket, EPOLL_CTL_DEL, client_socket, server_event);
	close(client_socket);
	return (0);
};

int	Webserver::add_client(int epoll_socket, int client_socket, struct epoll_event *server_event)
{
	fcntl(client_socket, F_SETFL, O_NONBLOCK);
	server_event->events = EPOLLIN | EPOLLET;
	server_event->data.fd = client_socket;
	if (epoll_ctl(epoll_socket, EPOLL_CTL_ADD, client_socket, server_event) == -1)
	{
		perror("epoll_ctl: client_socket");
		return (1);
	}
	return (0);
};

int	Webserver::wait_epoll(int epoll_socket, struct epoll_event *events)
{
	int			nb_ready_fd;
	const int	maxevents = MAX_EVENTS;
	const int	timeout = -1;

	nb_ready_fd = epoll_wait(epoll_socket, events, maxevents, timeout);
	if (nb_ready_fd == -1)
	{
		error("epoll_wait() failed.", NULL);
		perror("epoll_wait");
	}
	return (nb_ready_fd);
};

int	Webserver::add_to_interest_list(int epoll_socket, int server_socket, struct epoll_event *server_event)
{
	bzero(server_event, sizeof(*server_event));
	server_event->data.fd = server_socket;
	server_event->events = EPOLLIN;
	if (epoll_ctl(epoll_socket, EPOLL_CTL_ADD, server_socket, server_event) == -1)
	{
		error("epoll_ctl() failed.", NULL);
		perror("epoll_ctl: server_socket");
		return (1);
	}
	return (0);
};

int	Webserver::create_epoll_socket(int *epoll_socket)
{
	const int	flags = 0;	// Just create an epoll fd

	*epoll_socket = epoll_create1(flags);
	if (*epoll_socket == -1)
	{
		error("epoll_create1() failed.", NULL);
		perror("epoll_create1");
		return (1);
	}
	return (0);
};

// Listen for client connections on a socket
int Webserver::listen_server_socket(int server_socket)
{
	const int	backlog = 42;	// Maximum length to which the queue of
								// pending connections may grow

	if (listen(server_socket, backlog) == -1)
	{
		error("listen() failed.", NULL);
		perror("listen");
		return (1);
	}
	return (0);
};

int Webserver::accept_connexion(int server_socket, struct sockaddr_in server_address, int *client_socket)
{
	int addrlen = sizeof(server_address);

	*client_socket = accept(server_socket, (struct sockaddr *)&server_address, (socklen_t *)&addrlen);
	if (*client_socket == -1)
	{
		error("accept() failed.", NULL);
		perror("accept");
		return (1);
	}
	return (0);
};

// Assigns the server_address specified by addr to the socket referred to by the file descriptor server_socket.
int	Webserver::bind_address_to_server_socket(struct sockaddr_in *server_address, int server_socket)
{
	const sockaddr	*addr			= (const sockaddr *)server_address;	// Pointer on server_address
	socklen_t		addrlen			= sizeof(*server_address);			// Size, in bytes, of the server_address
																		// structure pointed to by addr

	server_address->sin_family			= AF_INET;						// IPv4 Internet protocols
	server_address->sin_addr.s_addr		= inet_addr("127.0.0.1");		// IP
	server_address->sin_port			= htons(8080);					// PORT

	if (bind(server_socket, addr, addrlen) == -1)
	{
		error("bind() failed.", NULL);
		perror("bind");
		return (1);
	}
	return (0);
};

int		Webserver::launch(void)
{
	int					epoll_socket;
	//struct epoll_event	events[MAX_EVENTS];
	//ssize_t				nb_events;
	//int					client_socket;

	if (create_epoll_socket(&epoll_socket))
		return (1);
	for (int i = 0 ; i < nb_of_servers ; ++i)
	{
		// /!\ A MODIFIER : Ca devrait etre des methodes de la classe Server !
		// (sauf ajout a la liste d'interet)
		// 1 socket par server avec IP/port provenant du fichier de config
		if (create_server_socket(&(server[i].server_socket)))
			return (1);
		if (bind_address_to_server_socket(&(server[i].server_address), server[i].server_socket))
			return (1);
		if (listen_server_socket(server[i].server_socket))
			return (1);
		// a ajouter a la liste d'interet d'epoll
		if (add_to_interest_list(epoll_socket, server[i].server_socket, &(server[i].server_event)))
			return (1);
	}
	while (true)
	{
	//	if ((nb_events = wait_epoll(epoll_socket, events)) == -1)
	//		return (1);
	//	for (ssize_t i = 0 ; i < nb_events ; ++i)
	//	{
	//		for (int j = 0 ; j < 1 /* nb_of_servers */ ; ++j)
	//		{
	//			if (events[i].data.fd == server_socket)
	//			{
	//				if (accept_connexion(server_socket, server_address, &client_socket))
	//					return (1);
	//				if (add_client(epoll_socket, client_socket, &server_event))
	//					return (1);
	//			}
	//			else
	//			{
	//				char request[1024];
	//				memset(request, 0, 1024);
	//				recv(events[i].data.fd, request, 1024, 0);
	//				std::cout << request << std::endl;

	//				char response[1024];
	//				strcpy(response, "Response : OK\n");
	//				send(events[i].data.fd, response, strlen(response), 0);

	//				if (remove_client(epoll_socket, client_socket, &server_event))
	//					return (1);
	//			}
	//		}
	//	}
	}
	return (0);
};
