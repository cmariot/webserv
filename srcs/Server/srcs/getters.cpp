#include "Server.hpp"

const std::pair<std::string, int> &	Server::get_address(void)	const
{
	return (_address);
};

const std::string &	Server::get_host(void) const
{
	return (_address.first);
};

const int &		Server::get_port(void) const
{
	return (_address.second);
};

const std::set<std::string> &	Server::get_server_names(void)	const
{
	return (_server_names);
};

const double &	Server::get_max_size(void)	const
{
	return (_client_max_body_size);
};

const std::map<int, Error_page> &	Server::get_error_pages(void)	const
{
	return (_error_pages);
};

const std::map<std::string, Location> &	Server::get_locations(void)		const
{
	return (_locations);
};
