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

int Webserver::accept_connexion(int tcp_socket, struct sockaddr_in address, int *accepted_socket)
{
	int addrlen = sizeof(address);

	*accepted_socket = accept(tcp_socket, (struct sockaddr *)&address, (socklen_t *)&addrlen);
	if (*accepted_socket == -1)
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
	// Toutes les addresses et tous les ports ?
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

#define MAX_EVENTS 10

int		Webserver::launch(void)
{
	int					tcp_socket;
	struct sockaddr_in	address;

	if (create_socket(&tcp_socket))
		return (1);
	if (bind_socket_and_address(tcp_socket, &address))
		return (1);
	if (listen_socket(tcp_socket))
		return (1);

	struct epoll_event	ev;
	struct epoll_event	events[MAX_EVENTS];
	int					conn_sock;
	int					nfds;
	int					epollfd;

	epollfd = epoll_create1(0);
	if (epollfd == -1)
	{
		perror("epoll_create1");
		exit(EXIT_FAILURE);
	}

	bzero(&ev, sizeof(ev));
	ev.events = EPOLLIN;
	ev.data.fd = tcp_socket;
	if (epoll_ctl(epollfd, EPOLL_CTL_ADD, tcp_socket, &ev) == -1)
	{
		perror("epoll_ctl: listen_sock");
		exit(EXIT_FAILURE);
	}

	while (true)
	{
		nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
		if (nfds == -1) {
			perror("epoll_wait");
			exit(EXIT_FAILURE);
		}

		for (int n = 0 ; n < nfds ; ++n)
		{
			if (events[n].data.fd == tcp_socket)
			{
				if (accept_connexion(tcp_socket, address, &conn_sock))
					return (1);
				conn_sock = fcntl(conn_sock, F_SETFL, O_NONBLOCK);
				if (conn_sock == -1)
					return (error("fcntl", NULL));
				ev.events = EPOLLIN | EPOLLET;
				ev.data.fd = conn_sock;
				if (epoll_ctl(epollfd, EPOLL_CTL_ADD, conn_sock, &ev) == -1)
				{
					perror("epoll_ctl: conn_sock");
					exit(EXIT_FAILURE);
				}

			}
			else
			{
				//do_use_fd(events[n].data.fd);
			}
		}
	}

	return (0);
};
