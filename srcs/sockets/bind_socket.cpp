/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind_socket.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:07:34 by cmariot           #+#    #+#             */
/*   Updated: 2022/10/11 11:07:43 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

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
