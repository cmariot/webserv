
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

		std::pair<std::string, int>			address;
		std::vector<std::string>			server_names;
		double								client_max_body_size;
		std::vector<Error_page>				error_pages;
		std::vector<Location>				locations;

		int									server_socket;
		struct sockaddr_in					server_address;

		Server();
		~Server();

		int			set_server_arguments(std::vector<std::string> &);

		int			create_server_socket(void);
		int			set_server_socket_options(void);
		int			bind_server_address(void);
		int			listen_for_clients(void) const;

	private :

		int			parse_listen_directive(std::vector<std::string> &, size_t &);
		int			parse_server_names_directive(std::vector<std::string> &, size_t &);
		int			parse_error_page_directive(std::vector<std::string> &, size_t &);
		int			parse_client_max_body_size_directive(std::vector<std::string> &, size_t &);
		int			parse_location_context(std::vector<std::string> &, size_t &);

		int			set_ip_and_port(std::vector<std::string> &, size_t &);
		std::string	set_ip(std::string);
		int			set_client_max_body_size(std::string &);

};

#endif
