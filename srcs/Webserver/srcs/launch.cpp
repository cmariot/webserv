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
# include <poll.h>

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

	const size_t		max_clients = 30;
	std::vector<int>	client_sockets(max_clients);

	fd_set			readfds;
	int				accepted_socket;
	int				max_socket;

	while (true)
	{
		FD_ZERO(&readfds);	// Initialize / Reset the FD set
		FD_SET(tcp_socket, &readfds);	// Add the tcp_socket to the FD set
		max_socket = tcp_socket;
		for (size_t i = 0 ; i < max_clients ; ++i)
		{
			if (client_sockets[i] > 0)
				FD_SET(client_sockets[i], &readfds); // Add the client_sockets[i] to the FD set
			if (client_sockets[i] > max_socket)
				max_socket = client_sockets[i];
		}
		if (select(max_socket + 1, &readfds, NULL, NULL, NULL) == -1)
			return (error("select()", NULL));
		if (FD_ISSET(tcp_socket, &readfds))	// If the tcp_socket still inside the FD set
		{
			if (accept_connexion(tcp_socket, address, &accepted_socket))
				return (1);
			std::cout << "New connection, socket fd is " << accepted_socket
				<< " ip is : " << inet_ntoa(address.sin_addr)
				<< " port : " << ntohs(address.sin_port) << std::endl;
			for (size_t i = 0 ; i < max_clients ; ++i)	// Add the accepted_socket value to the list of client_sockets
			{
				if (client_sockets[i] == 0)
				{
					client_sockets[i] = accepted_socket;
					break ;
				}
			}
		}
		for (size_t i = 0 ; i < max_clients ; ++i)
		{
			if (FD_ISSET(client_sockets[i], &readfds))
			{
				char request[1024];
				memset(request, 0, 1024);
				recv(client_sockets[i], request, 1024, 0);
				std::cout << request << std::endl;

				char response[1024];
				strcpy(response, "Response : OK\n\n");
				send(client_sockets[i], response, strlen(response), 0);
				
				std::cout << "Connection closed for the client whith the socket " << accepted_socket
					<< " on the ip " << inet_ntoa(address.sin_addr)
					<< " and the port " << ntohs(address.sin_port) << std::endl;
				
				close(client_sockets[i]);
				client_sockets[i] = 0;
				if (request[0] == '\0')
				{
					std::cout << "Empty request -> server shutdown" << std::endl;
					shutdown(tcp_socket, SHUT_RDWR);
					close(tcp_socket);
					return (0);
				}
			}
		}
	}
	shutdown(tcp_socket, SHUT_RDWR);
	close(tcp_socket);
	return (0);
};
