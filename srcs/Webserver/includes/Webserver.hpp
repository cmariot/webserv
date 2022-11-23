#ifndef WEBSERVER_HPP
# define WEBSERVER_HPP

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <cstring>

#include <string>
#include <vector>
#include <vector>
#include <istringstream>

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

		int						main_socket;

		std::vector<Server>		server;
		static size_t			nb_of_servers;

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

		// reponse : A deplacer dans response non ?
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
