
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
# include <signal.h>

# define MAX_EVENTS	10
# define STDIN		0
# define STDOUT		1
# define STDERR		2

# define SUCCESS	0
# define FAILURE	1

# include "Server.hpp"
# include "Utils.hpp"

using std::string;
using std::cout;
using std::endl;

class Webserver
{

	private:

		std::vector<Server>		server;
		static ssize_t			nb_of_servers;
		int						epoll_socket;

	public:

		Webserver(void);
		~Webserver(void);

		int		parse(int argc, const char *argv[]);
		int		launch(void);

	private:

		//	parsing
		int		get_file(const char *argv[], std::vector<std::string> &);
		int		parse_configuration_file(std::vector<std::string> &);
		int		remove_commentaries(std::vector<std::string> &) const;
		int		replace_blank_characters(std::vector<std::string> &) const;
		int		split_strings(std::vector<std::string> &, std::vector<std::string>	&) const;
		int		separate_braces(std::vector<std::string> &) const;
		int		separate_semicolon(std::vector<std::string>	& tokens_vector) const;

		//	servers initialization
		int		parse_server(std::vector<std::string> &);
		int		get_server_directives(std::vector<std::string> &, size_t &, size_t &, size_t &);

		// launch
		int		init_sockets(void);
		int		create_epoll_socket(void);
		int		add_to_interest_list(Server *);
		bool	client_connexion(ssize_t *, struct epoll_event &);
		int		accept_connexion(int *, Server &);
		int		add_client(int, struct epoll_event *);
		int		wait_event(struct epoll_event *);
		int		remove_client(int, int, struct epoll_event *);

		// reponse
		string	stored_file(string path);
		string	create_http_response(string method, string path);
		string	server_http_header_response(string method, string path);
		int 	server_response(int ,char *);

		//	error
		int		usage(void) const;

		// signal catcher
		int		catch_signal(void);

		// exit
		int		exit_webserv(void);

};

#endif
