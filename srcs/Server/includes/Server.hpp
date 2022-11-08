#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <vector>
# include <string>
# include <climits>
# include <cstdio>

# include <sys/socket.h>
# include <sys/epoll.h>
# include <netinet/in.h>
# include <arpa/inet.h>

# include "Utils.hpp"
# include "Error_page.hpp"
# include "Location.hpp"

class	Server
{

	public:

		Server(void);
		~Server(void);

		int							parse(std::vector<std::string> &);

	private:

		std::pair<std::string, int>	_address;
		std::vector<std::string>	_server_names;
		double						_client_max_body_size;
		std::vector<Error_page>		_error_pages;
		std::vector<Location>		_locations;

		bool						address_set;
		bool						server_names_set;
		bool						client_max_body_size_set;
		bool						error_page_set;
		bool						locations_set;

		int							set_listen(std::vector<std::string> &, size_t &);
		int							set_server_names(std::vector<std::string> &, size_t &);
		int							set_error_pages(std::vector<std::string> &, size_t &);
		int							set_client_max_body_size(std::vector<std::string> &, size_t &);
		int							set_client_max_body_size(std::string &);
		int							set_location(std::vector<std::string> &, size_t &);
		int							set_ip_and_port(std::vector<std::string> &, size_t &);

	public:

		std::pair<std::string, int>	get_address(void)				const;
		std::vector<std::string>	get_server_names(void)			const;
		double						get_client_max_body_size(void)	const;
		std::vector<Error_page>		get_error_pages(void)			const;
		std::vector<Location>		get_locations(void)				const;
		int							get_server_socket(void)			const;
		struct sockaddr_in			get_server_address(void)		const;

		int							_server_socket;
		struct sockaddr_in			_server_address;

		int							create_server_socket(void);
		int							set_server_socket_options(void);
		int							bind_server_address(void);
		int							listen_for_clients(void)		const;

};

#endif
