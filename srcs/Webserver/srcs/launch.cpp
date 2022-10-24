#include "Webserver.hpp"

# include <sys/types.h>
# include <errno.h>
# include <netinet/in.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <iostream>
# include <cstdio>
# include <cstdlib>
# include <cstring>
# include <unistd.h>
# include <sys/epoll.h>
# include <poll.h>
# include <fcntl.h>

#define MAX_EVENTS 10

int	Webserver::remove_client(int epoll_socket, int client_socket, struct epoll_event *ev)
{
	epoll_ctl(epoll_socket, EPOLL_CTL_DEL, client_socket, ev);
	close(client_socket);
	return (0);
}

int	Webserver::add_client(int epoll_socket, int client_socket, struct epoll_event *ev)
{
	fcntl(client_socket, F_SETFL, O_NONBLOCK);
	ev->events = EPOLLIN | EPOLLET;
	ev->data.fd = client_socket;
	if (epoll_ctl(epoll_socket, EPOLL_CTL_ADD, client_socket, ev) == -1)
	{
		perror("epoll_ctl: client_socket");
		return (1);
	}
	return (0);
}

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
}

int	Webserver::add_tcp_socket_to_epoll(int epoll_socket, int tcp_socket, struct epoll_event *ev)
{
	bzero(ev, sizeof(*ev));
	ev->events = EPOLLIN;
	ev->data.fd = tcp_socket;
	if (epoll_ctl(epoll_socket, EPOLL_CTL_ADD, tcp_socket, ev) == -1)
	{
		error("epoll_ctl() failed.", NULL);
		perror("epoll_ctl: tcp_socket");
		return (1);
	}
	return (0);
}

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
}

// Listen for client connections on a socket
int Webserver::listen_socket(int tcp_socket)
{
	const int	backlog = 5;	// Maximum length to which the queue of
								// pending connections may grow

	if (listen(tcp_socket, backlog) == -1)
	{
		error("listen() failed.", NULL);
		perror("listen");
		return (1);
	}
	return (0);
}

int Webserver::accept_connexion(int tcp_socket, struct sockaddr_in address, int *client_socket)
{
	int addrlen = sizeof(address);

	*client_socket = accept(tcp_socket, (struct sockaddr *)&address, (socklen_t *)&addrlen);
	if (*client_socket == -1)
	{
		error("accept() failed.", NULL);
		perror("accept");
		return (1);
	}
	return (0);
}

// Assigns the address specified by addr to the socket referred to by the file descriptor tcp_socket.
int	Webserver::bind_socket_and_address(int tcp_socket, struct sockaddr_in *address)
{
	const sockaddr	*addr			= (const sockaddr *)address;	// Pointer on address
	socklen_t		addrlen			= sizeof(*address);				// Size, in bytes, of the address
																	// structure pointed to by addr

	address->sin_family				= AF_INET;						// IPv4 Internet protocols
	address->sin_addr.s_addr		= inet_addr("127.0.0.1");		// IP
	address->sin_port				= htons(8080);					// PORT

	if (bind(tcp_socket, addr, addrlen) == -1)
	{
		error("bind() failed.", NULL);
		perror("bind");
		return (1);
	}
	return (0);
}

// Set options on sockets
int	Webserver::set_sockets_options(int tcp_socket)
{
	const int		level			= SOL_SOCKET;					// Option at the Socket API level
	const int		option_name		= SO_REUSEADDR | SO_REUSEPORT;	//
	const int		options			= 1;							//
	const void *	option_value	= &options;						//
	const socklen_t	option_len		= sizeof(options);				//

	if (setsockopt(tcp_socket, level, option_name, option_value, option_len) == -1)
	{
		error("setsockopt() failed.", NULL);
		perror("setsockopt");
		return (1);
	}
	return (0);
}

// Create a socket
int	Webserver::create_socket(int *tcp_socket)
{
	const int	socket_family	= AF_INET;		// IPv4 Internet protocols
	const int	socket_type		= SOCK_STREAM;	// TCP
	const int	protocol		= IPPROTO_TCP;	// IP

	*tcp_socket = socket(socket_family, socket_type, protocol);
	if (*tcp_socket == -1)
	{
		error("socket() failed.", NULL);
		perror("socket");
		return (1);
	}
	if (set_sockets_options(*tcp_socket))
		return (1);
	return (0);
}

int		Webserver::launch(void)
{
	int					tcp_socket;
	struct sockaddr_in	address;
	int					epoll_socket;
	struct epoll_event	ev;
	int					nb_events;
	struct epoll_event	events[MAX_EVENTS];
	int					client_socket;

	if (create_socket(&tcp_socket))
		return (1);
	if (bind_socket_and_address(tcp_socket, &address))
		return (1);
	if (listen_socket(tcp_socket))
		return (1);
	if (create_epoll_socket(&epoll_socket))
		return (1);
	if (add_tcp_socket_to_epoll(epoll_socket, tcp_socket, &ev))
		return (1);
	while (true)
	{
		if ((nb_events = wait_epoll(epoll_socket, events)) == -1)
			return (1);
		for (int i = 0 ; i < nb_events ; ++i)
		{
			if (events[i].data.fd == tcp_socket)
			{
				if (accept_connexion(tcp_socket, address, &client_socket))
					return (1);
				if (add_client(epoll_socket, client_socket, &ev))
					return (1);
			}
			else
			{
				char request[1024];
				memset(request, 0, 1024);
				recv(events[i].data.fd, request, 1024, 0);
				std::cout << request << std::endl;

				char response[1024];
				strcpy(response, "Response : OK\n");
				send(events[i].data.fd, response, strlen(response), 0);

				if (remove_client(epoll_socket, client_socket, &ev))
					return (1);
			}
		}
	}
	return (0);
};
