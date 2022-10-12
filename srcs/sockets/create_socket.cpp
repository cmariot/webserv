/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_socket.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:06:56 by cmariot           #+#    #+#             */
/*   Updated: 2022/10/11 11:07:12 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

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
