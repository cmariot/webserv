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
# include <sys/wait.h>

# define MAX_EVENTS	100

# define STDIN		0
# define STDOUT		1
# define STDERR		2

# define SUCCESS	0
# define FAILURE	1

# define INFO 0

# include "Server.hpp"
# include "Utils.hpp"
# include "Request.hpp"
# include "Response.hpp"

using std::string;
using std::cout;
using std::endl;

class Webserver
{

	private:

		std::vector<Server>		server;
		static size_t			nb_of_servers;
		int						main_socket;

		Request					_request;
		Response				_response;

	public:

		Webserver(void);
		~Webserver(void);

		size_t				nb_events;
		struct epoll_event	events[MAX_EVENTS];

		int		parse(int argc, const char *argv[]);
		int		launch(char *const *env);

	private:

		//	parsing
		int		check_arguments(int argc, const char *argv[]);
		int		get_file(const char *, std::vector<std::string> &);
		int		parse_configuration_file(std::vector<std::string> &);
		int		remove_commentaries(std::vector<std::string> &) const;
		int		replace_blank_characters(std::vector<std::string> &) const;
		int		split_strings(std::vector<std::string> &, std::vector<std::string>	&) const;
		int		separate_braces(std::vector<std::string> &) const;
		int		separate_semicolon(std::vector<std::string>	& tokens_vector) const;

		//	servers initialization
		int		parse_server(std::vector<std::string> &);
		int		get_server_directives(std::vector<std::string> &, size_t &, size_t &, size_t &);

		void	print_config(void) const;

		// signal catcher
		int		catch_signal(void);

		// launch
		int		init_sockets(void);
		int		create_main_socket(void);
		int		add_to_interest_list(Server *);
		bool	client_connexion(size_t *, struct epoll_event &);
		int		accept_connexion(int *, Server &, struct epoll_event *);
		int		add_client(int, struct epoll_event *);
		int		wait_event(struct epoll_event *, size_t &);
		int		remove_client(int, int, struct epoll_event *);

		int		get_server(Server &);

		// reponse
		string	stored_file(string path);
		string	create_http_response(string method, string path);
		string	server_http_header_response(string method, string path);
		int 	server_response(int ,char *);

		//	error
		int		usage(void) const;

		// exit
		int		exit_webserv(void);

};

#endif
