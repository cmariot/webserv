#include "Server.hpp"

size_t	ft_atoi(std::string str)
{
	size_t	result = 0;
	size_t	result_len = 0;
	size_t	i = 0;

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
	return (ft_atoi(port));
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
			if (digit_len > 3 || digit > 255 || (ip[i] != '.' && ip[i] != '\0'))
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

int	Server::set_ip_and_port(std::vector<std::string> & token_vector, size_t & i)
{
	size_t	pos;

	pos = token_vector[++i].find(":");
	if (pos != std::string::npos)
	{
		address.first = set_ip(token_vector[i].substr(0, pos));
		address.second = set_port(token_vector[i].substr(pos + 1));
	}
	else
	{
		if (token_vector[i].find(".") != std::string::npos || token_vector[i] == "*" || token_vector[i] == "localhost")
		{
			address.first = set_ip(token_vector[i]);
			address.second = 8000;
		}
		else
		{
			address.first = "127.0.0.1";
			address.second = set_port(token_vector[i]);
		}
	}
	return (0);
};

bool	Server::invalid_directive_len(std::vector<std::string> & vector, size_t begin_index, std::string untill,
		size_t min_len, size_t max_len)
{
	size_t	line_len = 0;

	while (begin_index + line_len < vector.size())
	{
		++line_len;
		if (vector[begin_index + line_len] == untill)
		{
			++line_len;
			break ;
		}
	}
	if (line_len > min_len || line_len < max_len)
		return (true);
	else
		return (false);
}

int	Server::parse_listen_directive(std::vector<std::string> & token_vector, size_t & i)
{
	if (invalid_directive_len(token_vector, i, ";", 3, 3))
		return (error("Syntax error : invalid listen directive."));
	else if (set_ip_and_port(token_vector, i))
		return (1);
	else if (token_vector[++i] != ";")
		return (error("Syntax error : the listen directive doesn't ends by ';'."));
	return (0);
};
