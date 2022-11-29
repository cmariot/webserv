#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <vector>
# include <set>
# include <map>
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

using std::string;
using std::vector;
using std::cout;
using std::endl;

class	Server
{

	public:

		Server(void);
		~Server(void);

		int		parse(std::vector<string> &);

	private:

		std::pair<string, int>		_address;
		std::set<string>			_server_names;
		double						_client_max_body_size;
		std::map<int, Error_page>	_error_pages;
		std::map<string, Location>	_locations;

		bool	address_set;
		bool	server_names_set;
		bool	client_max_body_size_set;
		bool	error_page_set;
		bool	locations_set;

		int		set_listen(std::vector<string> &, size_t &);
		int		set_server_names(std::vector<string> &, size_t &);
		int		set_error_pages(std::vector<string> &, size_t &);
		int		set_client_max_body_size(std::vector<string> &, size_t &);
		int		set_client_max_body_size(string &);
		int		set_location(std::vector<string> &, size_t &);
		int		set_ip_and_port(std::vector<string> &, size_t &);

	public:

		const std::pair<string, int> &		get_address(void)		const;
		const string &						get_host(void)			const;
		const int &							get_port(void)			const;
		const std::set<string> &			get_server_names(void)	const;
		const double &						get_max_size(void)		const;
		const std::map<int, Error_page> &	get_error_pages(void)	const;
		const std::map<string, Location> &	get_locations(void)		const;

	public:

		int					socket;
		struct sockaddr		address;
		struct epoll_event	event;
		int					addrlen;

};

#endif
