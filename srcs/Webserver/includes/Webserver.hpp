/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserver.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:04:09 by cmariot           #+#    #+#             */
/*   Updated: 2022/10/24 15:01:14 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERVER_HPP
# define WEBSERVER_HPP

# include <vector>
# include <string>
# include <fstream>
# include <istream>
# include <iostream>
# include <sstream>
# include <climits>

# include "Server.hpp"

class Webserver
{

	private:

		std::vector<Server>		server;

	public:

		Webserver(void);
		~Webserver(void);

		int		parse(int argc, const char *argv[]);
		int		launch(void);

	private:

		//	parsing
		int		parse_configuration_file(std::vector<std::string> &);
		int		remove_commentaries(std::vector<std::string> &) const;
		int		replace_blank_characters(std::vector<std::string> & string_vector) const;
		int		split_strings(std::vector<std::string> &, std::vector<std::string>	&) const;
		int		separate_braces(std::vector<std::string> &) const;

		//	servers initialization
		int		parse_server(std::vector<std::string> &);

		// launch
		int		create_socket(int *);
		int		set_sockets_options(int);
		int		bind_socket_and_address(int, struct sockaddr_in *);
		int		listen_socket(int);
		int		create_epoll_socket(int *);
		int		accept_connexion(int, struct sockaddr_in, int *);
		int		add_tcp_socket_to_epoll(int, int, struct epoll_event *);
		int		wait_epoll(int, struct epoll_event *);
		int		add_client(int, int, struct epoll_event *);

		//	error
		int		usage(void) const;
		int		error(const char *error, const char *complement) const;

};

#endif
