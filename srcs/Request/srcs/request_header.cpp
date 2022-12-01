#include "Request.hpp"

// 2eme ligne de la requete,
// nous donne des informations sur le serveur auquel on va envoyer la reponse
int	Request::set_server_address(void)
{
	std::string		host;
	size_t			pos;
	const std::multimap<string, string>::const_iterator	it
		= _header.find("Host");

	if (it == _header.end())
		return (error("No Host in the header request, Error 400"));
	host = _header.find("Host")->second;
	pos = host.rfind(":");
	if (pos != std::string::npos)
	{
		_address.first = host.substr(0, pos);
		_address.second = set_port(host.substr(pos + 1));
	}
	else
	{
		if (only_digit(host))
		{
			_address.first = "0.0.0.0";
			_address.second = set_port(host);
		}
		else
		{
			_address.first = host;
			_address.second = 8080;
		}
	}
	return (0);
};

// Add the Key/Value pair of the request header in a map
int	Request::set_header(size_t & i)
{
	std::string		line;
	size_t			line_len;
	std::string		key;
	size_t			key_len;
	std::string		value;

	_header.clear();
	while (i + 3 < _request.size())
	{
		if (_request[i] == '\r' && _request[i + 1] == '\n'
			&& _request[i + 2] == '\r' && _request[i + 3] == '\n')
		{
			_header_size = i + 4;
			return (0);
		}
		else if (_request[i] == '\r' && _request[i + 1] == '\n')
			i += 2;
		line_len = 0;
		while (i + line_len + 1 < _request.size())
		{
			if (_request[i + line_len] == '\r' && _request[i + line_len + 1] == '\n')
				break ;
			++line_len;
		}
		line = _request.substr(i, line_len);
		key_len = 0;
		while (i + key_len < _request.size())
		{
			if (_request[i + key_len] == ':')
				break ;
			++key_len;
		}
		key = line.substr(0, key_len);
		if (key_len + 2 > line_len)
			continue ;
		value = line.substr(key_len + 2, (line_len - key_len + 2));
		_header.insert(std::pair<std::string, std::string>(key, value));
		i += line_len;
	}
	return (1);
};
