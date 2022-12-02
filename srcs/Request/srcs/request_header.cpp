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

	std::cout << _request << std::endl;
	_header.clear();
	while (i + 1 < _request.size())
	{
		line_len = 0;
		while (i + line_len + 1 < _request.size())
		{
			if (_request[i + line_len] == '\r' && _request[i + line_len + 1] == '\n')
				break ;
			++line_len;
		}
		line = _request.substr(i, line_len);
		key_len = 0;
		while (key_len < line_len)
		{
			if (_request[i + key_len] == ':')
				break ;
			++key_len;
		}
		key = line.substr(0, key_len);
		if (key_len + 2 >= line_len)
			break ;
		value = line.substr(key_len + 2, (line_len - key_len + 2));
		_header.insert(std::pair<std::string, std::string>(key, value));
		i += line_len + 2;
		if (i + 1 < _request.size() && _request[i] == '\r' && _request[i + 1] == '\n')
		{
			_header_size = i + 2;
			set_server_address();
			return (0);
		}
	}
	return (1);
};

bool	Request::header_in_this_request(size_t & i)
{
	if (i + 1 <= _request.size() && _request[i] == '\r' && _request[i + 1] == '\n')
		return (false);
	return (true);
};
