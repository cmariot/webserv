#include "Client.hpp"

const char *	Client::get_response(void) const
{
	return (_response._full_response.c_str());
};

size_t	Client::get_response_size(void) const
{
	return (_response._full_response.size());
};

std::string		Client::get_hostname(void) const
{
	return (_server.get_address().first);
};

int		Client::get_port(void) const
{
	return (_server.get_address().second);
};

std::pair<std::string, int>	Client::get_address(void) const
{
	return (_server.get_address());
};
