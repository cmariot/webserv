#include "Server.hpp"

// Set options on sockets
int	Server::set_server_socket_options(void)
{
	const int		level			= SOL_SOCKET;					// Option at the Socket API level
	const int		option_name		= SO_REUSEADDR | SO_REUSEPORT;	//
	const int		options			= 1;							//
	const void *	option_value	= &options;						//
	const socklen_t	option_len		= sizeof(options);				//

	if (setsockopt(server_socket, level, option_name, option_value, option_len) == -1)
	{
		error("setsockopt() failed.");
		perror("setsockopt");
		return (1);
	}
	return (0);
};

// Create a socket
int	Server::create_server_socket(void)
{
	const int	socket_family	= AF_INET;		// IPv4 Internet protocols
	const int	socket_type		= SOCK_STREAM;	// TCP
	const int	protocol		= IPPROTO_TCP;	// IP

	server_socket = socket(socket_family, socket_type, protocol);
	if (server_socket == -1)
	{
		error("socket() failed.");
		perror("socket");
		return (1);
	}
	if (set_server_socket_options())
		return (1);
	return (0);
};
