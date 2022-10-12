/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listen_socket.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:08:11 by cmariot           #+#    #+#             */
/*   Updated: 2022/10/11 11:08:19 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

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
