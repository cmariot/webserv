#include "Webserver.hpp"

#define SIGNAL_CAUGHT nb_events == -2

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

int	Webserver::wait_epoll(int epoll_socket, struct epoll_event *events)
{
	int			nb_ready_fd;
	const int	maxevents = MAX_EVENTS;
	const int	timeout = -1;

	nb_ready_fd = epoll_wait(epoll_socket, events, maxevents, timeout);
	if (nb_ready_fd == -1)
	{
		int err = errno;
		if (err == EINTR)
			return (-2);
		error("epoll_wait() failed.", NULL);
		perror("epoll_wait");
	}
	return (nb_ready_fd);
};

int	Webserver::add_to_interest_list(Server *server, int epoll_socket)
{
	struct epoll_event	event;
	
	bzero(&event, sizeof(event));
	event.data.fd = server->server_socket;
	event.events = EPOLLIN | EPOLLOUT | EPOLLRDHUP;
	if (epoll_ctl(epoll_socket, EPOLL_CTL_ADD, server->server_socket, &event) == -1)
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

int		Webserver::launch(void)
{
	int					epoll_socket;
	ssize_t				nb_events;
	struct epoll_event	events[MAX_EVENTS];
	int					client_socket;
	int					j;

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
	catch_signal();
	std::cout << "Waiting for new events ..." << std::endl;
	while (true)
	{
		nb_events = wait_epoll(epoll_socket, events);
		if (nb_events == -1)
			return (1);
		else if (SIGNAL_CAUGHT)
			return (exit_webserv(epoll_socket));
		for (ssize_t i = 0 ; i < nb_events ; ++i)
		{
			bool found = false;

			for (j = 0 ; j < nb_of_servers ; ++j)
			{
				if (events[i].data.fd == server[j].server_socket)
				{
					found = true;
					break ;
				}
			}
			if (found == true)
			{
				std::cout << "A client has just connected to the server " << server[j].ip << ":" << server[j].port << std::endl;
				if (accept_connexion(events[i].data.fd, server[j].server_address, &client_socket))
					return (1);
				if (add_client(epoll_socket, client_socket, events))
					return (1);
			}
			else
			{
				std::cout << "Event traitment" << std::endl;
				char request[1024];
				memset(request, 0, 1024);
				recv(events[i].data.fd, request, 1024, 0);
				std::cout << request << std::endl;

				char response[1024];
				strcpy(response, "Response : OK\n");
				send(events[i].data.fd, response, strlen(response), 0);

				if (remove_client(epoll_socket, client_socket, events))
					return (1);
			}
		}
	}
	return (0);
};
