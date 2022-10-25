/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserver.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:04:09 by cmariot           #+#    #+#             */
/*   Updated: 2022/10/25 17:40:05 by cmariot          ###   ########.fr       */
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
#include <signal.h>

#define MAX_EVENTS	10
#define STDIN		0
#define STDOUT		1
#define STDERR		2

# include "Server.hpp"

class Webserver
{

	private:

		std::vector<Server>		server;
		static ssize_t			nb_of_servers;

	public:

		Webserver(void);
		~Webserver(void);

		int		parse(int argc, const char *argv[]);
		int		launch(void);

	private:

		//	parsing
		int		parse_configuration_file(std::vector<std::string> &);
		int		remove_commentaries(std::vector<std::string> &) const;
		int		replace_blank_characters(std::vector<std::string> &) const;
		int		split_strings(std::vector<std::string> &, std::vector<std::string>	&) const;
		int		separate_braces(std::vector<std::string> &) const;

		//	servers initialization
		int		parse_server(std::vector<std::string> &);

		// launch
		int		create_epoll_socket(int *);
		int		add_to_interest_list(Server *, int);
		int		accept_connexion(int, struct sockaddr_in, int *);
		int		wait_event(int, struct epoll_event *);
		int		add_client(int, int, struct epoll_event *);
		int		remove_client(int, int, struct epoll_event *);

		//	error
		int		usage(void) const;
		int		error(const char *error, const char *complement) const;

		// signal catcher
		int		catch_signal(void);

		// exit
		int		exit_webserv(int);

};

#endif
