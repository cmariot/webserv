#include "Server.hpp"

size_t	ft_atoi(std::string str)
{
	size_t	result = 0;
	size_t	result_len = 0;
	size_t	i = 0;

	if (str.empty())
		return (-1);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i++] - '0';
		if (++result_len > 10)
			return (-1);
	}
	if (str[i])
		return (-1);
	return (result);
}

size_t	set_port(std::string port)
{
	size_t	digit = ft_atoi(port);

	if (digit >= 1 && digit <= 65535)
		return (digit);
	return (-1);
}

std::string	Server::set_ip(std::string ip)
{
	size_t	i = 0;

	if (ip.empty())
		return ("");
	else if (ip == "*")
		return ("0.0.0.0");
	else if (ip == "localhost")
		return ("127.0.0.1");
	else
	{
		int	digit_len = 0;
		int	digit = 0;
		int	nb_blocks = 0;

		while (i < ip.size())
		{
			while (i < ip.size() && isdigit(ip[i]) == true)
			{
				digit = digit * 10 + ip[i++] - '0';
				++digit_len;
			}
			if (digit_len == 0 || digit_len > 3 || digit > 255 || (ip[i] != '.' && ip[i] != '\0'))
				return ("");
			if (ip[i] == '\0')
				break ;
			++nb_blocks;
			digit = 0;
			digit_len = 0;
			++i;
		}
		if (ip[i] == '\0' && nb_blocks == 3)
			return (ip);
		else
			return ("");
	}
};

// listen 127.0.0.1:8000;
// listen 127.0.0.1;
// listen 8000;
// listen *:8000;
// listen localhost:8000;

int	Server::set_ip_and_port(std::vector<std::string> & vector, size_t & i)
{
	size_t	pos;

	pos = vector[++i].find(":");
	if (pos != std::string::npos)
	{
		_address.first = set_ip(vector[i].substr(0, pos));
		_address.second = set_port(vector[i].substr(pos + 1));
	}
	else
	{
		if (vector[i].find(".") != std::string::npos || vector[i] == "*" || vector[i] == "localhost")
		{
			_address.first = set_ip(vector[i]);
			_address.second = 0;
		}
		else
		{
			_address.first = "127.0.0.1";
			_address.second = set_port(vector[i]);
		}
	}
	if (_address.first == "" || _address.second == -1)
		return (error("Invalid host:port in the listen directive."));
	return (0);
};

int	Server::set_listen(std::vector<std::string> & vector, size_t & i)
{
	if (invalid_directive_len(vector, i, ";", 3, 3))
		return (error("Syntax error : invalid listen directive."));
	else if (set_ip_and_port(vector, i))
		return (1);
	else if (vector[++i] != ";")
		return (error("Syntax error : the listen directive doesn't ends by ';'."));
	std::cout << "\tlisten\t\t\t" << _address.first << ":" << _address.second << ";" << std::endl;
	return (0);
};
