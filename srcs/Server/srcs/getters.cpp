#include "Server.hpp"

std::pair<std::string, int>	Server::get_address(void)	const
{
	return (_address);
};

std::set<std::string>	Server::get_server_names(void)	const
{
	return (_server_names);
};

double	Server::get_client_max_body_size(void)	const
{
	return (_client_max_body_size);
};

std::map<int, Error_page>	Server::get_error_pages(void)	const
{
	return (_error_pages);
};

std::map<std::string, Location>	Server::get_locations(void)		const
{
	return (_locations);
};

int		Server::get_server_socket(void)	const
{
	return (_server_socket);
};

struct sockaddr_in	Server::get_server_address(void)	const
{
	return (_server_address);
};
