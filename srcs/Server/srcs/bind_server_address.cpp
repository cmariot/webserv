#include "Server.hpp"

// Assigns the server_address specified by addr to the socket referred to by the file descriptor server_socket.
int	Server::bind_server_address(void)
{
	const sockaddr	*addr		= (const sockaddr *)&_server_address;	// Pointer on server_address
	socklen_t		addrlen		= sizeof(_server_address);				// Size, in bytes, of the server_address
																		// structure pointed to by addr

	_server_address.sin_family			= AF_INET;								// IPv4 Internet protocols
	_server_address.sin_addr.s_addr		= inet_addr(_address.first.c_str());		// IP
	_server_address.sin_port			= htons(_address.second);				// PORT
	if (bind(_server_socket, addr, addrlen) == -1)
	{
		error("bind() failed.");
		perror("bind");
		return (1);
	}
	return (0);
};
