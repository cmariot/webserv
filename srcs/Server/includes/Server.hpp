#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <vector>
# include <string>
# include <sys/socket.h>
# include <sys/epoll.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <errno.h>
# include <cstdio>
# include "climits"

# include "Utils.hpp"
# include "Error_page.hpp"
# include "Location.hpp"

class	Server
{

	public:

		Server(void);
		~Server(void);

		int			parse(std::vector<std::string> &);

		int			create_server_socket(void);
		int			set_server_socket_options(void);
		int			bind_server_address(void);
		int			listen_for_clients(void) const;

		// a passer private par la suite
		int									_server_socket;
		struct sockaddr_in					_server_address;
		std::pair<std::string, int>			_address;
		std::vector<std::string>			_server_names;
		double								_client_max_body_size;
		std::vector<Error_page>				_error_pages;
		std::vector<Location>				_locations;

	private :

		int			set_listen(std::vector<std::string> &, size_t &);
		int			set_server_names(std::vector<std::string> &, size_t &);
		int			set_error_pages(std::vector<std::string> &, size_t &);
		int			set_client_max_body_size(std::vector<std::string> &, size_t &);
		int			set_client_max_body_size(std::string &);
		int			set_location(std::vector<std::string> &, size_t &);

		int			set_ip_and_port(std::vector<std::string> &, size_t &);
		std::string	set_ip(std::string);

};

#endif
