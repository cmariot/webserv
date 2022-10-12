/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:21:52 by cmariot           #+#    #+#             */
/*   Updated: 2022/10/12 15:39:33 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

//	Webserver			webserv;
//
//	if (webserv.parse(argc, argv))
//		return (1);

int	main(void)
{

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
