/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:21:52 by cmariot           #+#    #+#             */
/*   Updated: 2022/10/19 14:06:34 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

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

int	display_error(std::string error_message)
{
	std::cerr 
		<< "Error: " << error_message
		<< std::endl;
	return (1);
}

int accept_connexion(int socket_fd, struct sockaddr_in address, int *accepted_socket)
{
	int addrlen = sizeof(address);

	*accepted_socket = accept(socket_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
	if (*accepted_socket == -1)
	{
		display_error("accept() failed.");
		perror("accept");
		return (1);
	}
	return (0);
}

// Listen for client connections on a socket
int listen_socket(int socket_fd)
{
	const int	backlog = 5;	// Maximum length to which the queue of
								// pending connections may grow

	if (listen(socket_fd, backlog) == -1)
	{
		display_error("listen() failed.");
		perror("listen");
		return (1);
	}
	return (0);
}

// Assigns the address specified by addr to the socket referred to by the file descriptor socket_fd.
int	bind_socket_and_address(int socket_fd, struct sockaddr_in *address)
{
	const sockaddr	*addr			= (const sockaddr *)address;	// Pointer on address
	socklen_t		addrlen			= sizeof(*address);				// Size, in bytes, of the address
																	// structure pointed to by addr

	address->sin_family				= AF_INET;						// IPv4 Internet protocols
	address->sin_addr.s_addr		= inet_addr("127.0.0.1");		// IP
	address->sin_port				= htons(8080);					// PORT

	if (bind(socket_fd, addr, addrlen) == -1)
	{
		display_error("bind() failed.");
		perror("bind");
		return (1);
	}
	return (0);
}

// Set options on sockets
int	set_sockets_options(int socket_fd)
{
	const int		level			= SOL_SOCKET;					// Option at the Socket API level
	const int		option_name		= SO_REUSEADDR | SO_REUSEPORT;	//
	const int		options			= 1;							//
	const void *	option_value	= &options;						//
	const socklen_t	option_len		= sizeof(options);				//

	if (setsockopt(socket_fd, level, option_name, option_value, option_len) == -1)
	{
		display_error("setsockopt() failed.");
		perror("setsockopt");
		return (1);
	}
	return (0);
}

// Create an endpoint for communication and
// returns a file descriptor that refers to that endpoint
int	create_socket(int *socket_fd)
{
	const int	domain		= AF_INET;		// IPv4 Internet protocols
	const int	type		= SOCK_STREAM;	// TCP
	const int	protocol	= 0;			// IP

	*socket_fd = socket(domain, type, protocol);
	if (*socket_fd == -1)
	{
		display_error("socket() failed.");
		perror("socket");
		return (1);
	}
	if (set_sockets_options(*socket_fd))
		return (1);
	return (0);
}

int	main(int argc, const char *argv[])
{
	Webserver	webserv;

	if (webserv.parse(argc, argv))
		return (1);


	int					socket_fd;
	struct sockaddr_in	address;
	int					accepted_socket;

	if (create_socket(&socket_fd))
		return (1);
	if (bind_socket_and_address(socket_fd, &address))
		return (1);
	if (listen_socket(socket_fd))
		return (1);
	if (accept_connexion(socket_fd, address, &accepted_socket))
		return (1);

	// Received request from the client
	char request[1024];
	memset(request, 0, 1024);
	if (recv(accepted_socket, request, 1024, 0) != -1)
		printf("%s\n", request);

	// Send a response to the client
	char response[1024];
	strcpy(response, "Hello from server");
	send(accepted_socket, response, strlen(response), 0);

	close(accepted_socket);
	shutdown(socket_fd, SHUT_RDWR);
	return (0);
}
