/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:44:38 by cmariot           #+#    #+#             */
/*   Updated: 2022/10/25 09:09:10 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <cstdio>

class	Server
{

	public:

		std::string				ip;
		int						port;
		std::string				server_name;
		std::vector<void *>		error_pages;
		size_t					max_body_size;
		std::vector<void *>		locations;

		int						server_socket;
		struct sockaddr_in		server_address;
		struct epoll_event		server_event;

	public:

		Server(int id);

		~Server();

		int	set_server_arguments(std::vector<std::string> &, std::string, size_t);

		int	create_server_socket(void);
		int	set_server_socket_options(void);
		int	bind_server_address(void);
		int listen_for_clients(void) const;

};

#endif
