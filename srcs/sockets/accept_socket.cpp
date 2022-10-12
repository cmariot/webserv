/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accept_socket.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:08:56 by cmariot           #+#    #+#             */
/*   Updated: 2022/10/11 11:09:09 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

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
