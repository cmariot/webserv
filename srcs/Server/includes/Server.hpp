/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:44:38 by cmariot           #+#    #+#             */
/*   Updated: 2022/10/24 20:39:07 by cmariot          ###   ########.fr       */
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

class	Server
{

	public:

		int						server_socket;
		struct sockaddr_in		server_address;
		struct epoll_event		server_event;

		std::string				ip;
		int						port;
		std::string				server_name;
		std::vector<void *>		error_pages;
		size_t					max_body_size;
		std::vector<void *>		locations;

	public:

		Server();

		~Server();

		int	set_server_arguments(std::vector<std::string> &);

};

#endif
