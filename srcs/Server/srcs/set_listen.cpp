#include "Server.hpp"

// listen 127.0.0.1:8000;
// listen 127.0.0.1;
// listen 8000;
// listen *:8000;
// listen localhost:8000;

int	Server::set_ip_and_port(std::vector<std::string> & vector, size_t & i)
{
	size_t	pos;

	pos = vector[++i].rfind(":");
	if (pos != std::string::npos)
	{
		_address.first = set_ip(vector[i].substr(0, pos));
		_address.second = set_port(vector[i].substr(pos + 1));
	}
	else
	{
		if (only_digit(vector[i]))
		{
			_address.first = "0.0.0.0";
			_address.second = set_port(vector[i]);
		}
		else
		{
			_address.first = set_ip(vector[i]);
			_address.second = 8080;
		}
	}
	if (_address.first == "" || _address.second == -1)
		return (error("Invalid host:port in the listen directive."));
	return (0);
};

int	Server::set_listen(std::vector<std::string> & vector, size_t & i, const std::vector<Server> & servers)
{
	if (address_set)
		return (error("Syntax error, multiple listen directives."));
	if (invalid_directive_len(vector, i, ";", 3, 3))
		return (error("Syntax error : invalid listen directive."));
	else if (set_ip_and_port(vector, i))
		return (1);
	else if (vector[++i] != ";")
		return (error("Syntax error : the listen directive doesn't ends by ';'."));
	for (size_t j = 0 ; j < servers.size() - 1 ; ++j)
	{
		if (_address == servers[j].get_address())
			return (error("This address is already used by another server."));
	}
	address_set = true;
	return (0);
};
