/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:44:38 by cmariot           #+#    #+#             */
/*   Updated: 2022/10/28 10:59:34 by cmariot          ###   ########.fr       */
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

		std::pair<std::string, int>	address;		// Pair IP:Port
		std::string					server_name;
		size_t						max_body_size;
		std::vector<void *>			error_pages;
		std::vector<void *>			locations;

		int							server_socket;
		struct sockaddr_in			server_address;


		Server();
		~Server();

		int			set_server_arguments(std::vector<std::string> &);

		int			create_server_socket(void);
		int			set_server_socket_options(void);
		int			bind_server_address(void);
		int			listen_for_clients(void) const;

	private :

		int			parse_listen_directive(std::vector<std::string> &, size_t &);
		int			parse_server_name_directive(std::vector<std::string> &, size_t &);
		int			parse_error_page_directive(std::vector<std::string> &, size_t &);
		int			parse_client_max_body_size_directive(std::vector<std::string> &, size_t &);
		int			parse_location_context(std::vector<std::string> &, size_t &);

		bool		invalid_directive_len(std::vector<std::string> &, size_t, std::string, size_t, size_t);
		int			set_ip_and_port(std::vector<std::string> &, size_t &);
		std::string	set_ip(std::string);

		int			error(const char *error) const;
		int			error(const char *error, const char *complement) const;
};

#endif
