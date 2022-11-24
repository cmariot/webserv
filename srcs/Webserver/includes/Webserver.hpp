#ifndef WEBSERVER_HPP
# define WEBSERVER_HPP

# include <cstdio>
# include <cstdlib>
# include <unistd.h>
# include <errno.h>
# include <sys/socket.h>
# include <netdb.h>
# include <fcntl.h>
# include <sys/epoll.h>
# include <cstring>

# include <string>
# include <vector>
# include <sstream>

# include "Server.hpp"
# include "Utils.hpp"
# include "Request.hpp"
# include "Response.hpp"

# define STDIN			0
# define STDOUT			1
# define STDERR			2
# define MAX_EVENTS		200
# define SIGNAL_CAUGHT	1
# define INFO			0

using std::string;
using std::cout;
using std::endl;

class Webserver
{

	public:

		Webserver(void);
		~Webserver(void);

		int		parse(const int argc, const char *argv[], const char **env);
		int		launch(void);

	private:

		//	private members
		static size_t			nb_of_servers;
		std::vector<Server>		server;
		int						epoll_socket;
		struct epoll_event		events[MAX_EVENTS];;
		int						nb_events;
		bool					signal;
		const char				**_env;

		//	parsing
		int			check_arguments(const int & argc, const char *argv[]);
		int			get_file(const char * &, std::vector<std::string> &);
		int			parse_configuration_file(std::vector<std::string> &);
		int			remove_commentaries(std::vector<std::string> &) const;
		int			replace_blank_characters(std::vector<std::string> &) const;
		int			split_strings(std::vector<std::string> &, std::vector<std::string> &) const;
		int			separate_braces(std::vector<std::string> &) const;
		int			separate_semicolon(std::vector<std::string>	&) const;
		int			parse_server(std::vector<std::string> &);
		int			get_server_directives(std::vector<std::string> &, size_t &, size_t &, size_t &);

		//	print
		void		print_config(void) const;

		//	launch
		int			init_sockets(void);
		int			create_epoll_descriptor(void);
		int			open_server_socket(Server &);
		int			bind_server_address(Server &);
		int			listen_server(Server &);
		int			set_non_blocking(Server &);
		int			add_to_epoll_interest_list(Server &);

		int			catch_signal(void);
		int			new_events(void);
		int			client_disconnection(struct epoll_event &);
		bool		client_connection(struct epoll_event &);

		bool		add_to_ready_list(Server &);
		int			add_client(int &, struct epoll_event *);

		int			remove_client(const int &, struct epoll_event *);

		//	utils
		int			usage(void) const;
		int			exit_webserv(void);

		//	env
		void		set_env(const char *env[]);
		const char	**get_env(void) const;

};

#endif
