/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserver.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:04:09 by cmariot           #+#    #+#             */
/*   Updated: 2022/10/24 20:40:15 by cmariot          ###   ########.fr       */
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
# include <sys/types.h>
# include <errno.h>
# include <netinet/in.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <iostream>
# include <cstdio>
# include <cstdlib>
# include <cstring>
# include <unistd.h>
# include <sys/epoll.h>
# include <poll.h>
# include <fcntl.h>

#define MAX_EVENTS 10

# include "Server.hpp"

class Webserver
{

	private:

		std::vector<Server>		server;
		ssize_t					nb_of_servers;

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
		int		create_server_socket(int *);
		int		set_server_socket_options(int);
		int		bind_address_to_server_socket(struct sockaddr_in *, int);
		int		listen_server_socket(int);
		int		create_epoll_socket(int *);
		int		accept_connexion(int, struct sockaddr_in, int *);
		int		add_to_interest_list(int, int, struct epoll_event *);
		int		wait_epoll(int, struct epoll_event *);
		int		add_client(int, int, struct epoll_event *);
		int		remove_client(int, int, struct epoll_event *);

		//	error
		int		usage(void) const;
		int		error(const char *error, const char *complement) const;

};

#endif
