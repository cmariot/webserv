/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:44:38 by cmariot           #+#    #+#             */
/*   Updated: 2022/10/26 20:03:00 by cmariot          ###   ########.fr       */
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

		Server();
		~Server();

		std::string				ip;
		int						port;
		std::string				server_name;
		std::vector<void *>		error_pages;
		size_t					max_body_size;
		std::vector<void *>		locations;
		int						server_socket;
		struct sockaddr_in		server_address;

		int		set_server_arguments(std::vector<std::string> &);

		int		parse_listen_directive(std::vector<std::string> &, size_t &);
		int		parse_server_name_directive(std::vector<std::string> &, size_t &);
		int		parse_error_page_directive(std::vector<std::string> &, size_t &);
		int		parse_client_max_body_size_directive(std::vector<std::string> &, size_t &);
		int		parse_location_context(std::vector<std::string> &, size_t &);

		int		create_server_socket(void);
		int		set_server_socket_options(void);
		int		bind_server_address(void);
		int		listen_for_clients(void) const;

		int		error(const char *error) const;
		int		error(const char *error, const char *complement) const;
};

#endif
