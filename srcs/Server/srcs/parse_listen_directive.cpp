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
			return (0);
	}
	if (str[i])
		return (0);
	return (result);
}

std::string	set_ip(std::string ip)
{
	if (ip == "*")
		return ("0.0.0.0");
	else if (ip == "localhost")
		return ("127.0.0.1");
	else
	{
		return (ip);
	}
};

bool	correct_len(std::vector<std::string> & vector, size_t begin_index, std::string untill, size_t expected_len)
{
	size_t	line_len = 0;

	while (vector.begin() + (begin_index + line_len) != vector.end())
	{
		++line_len;
		if (vector[begin_index + line_len] == untill)
		{
			++line_len;
			break ;
		}
	}
	if (line_len == expected_len)
		return (true);
	else
		return (false);
}

// listen 127.0.0.1:8000;
// listen 127.0.0.1;
// listen 8000;
// listen *:8000;
// listen localhost:8000;

int	Server::parse_listen_directive(std::vector<std::string> & token_vector, size_t & i)
{
	size_t	pos;
	const std::string	default_ip = "";
	const size_t		default_port = 0;

	if (correct_len(token_vector, i, ";", 3) == false)
		return (error("Syntax error : invalid listen directive."));
	ip = default_ip;
	port = default_port;
	pos = token_vector[++i].find(":");
	if (pos != std::string::npos)
	{
		ip = set_ip(token_vector[i].substr(0, pos));
		port = ft_atoi(token_vector[i].substr(pos + 1));
	}
	else
	{
		if (token_vector[i] == "*")
		{
			ip = "0.0.0.0";
		}
		if (token_vector[i].find(".") != std::string::npos
				|| token_vector[i] == "localhost"
				|| token_vector[i] == "*")
		{
			ip = set_ip(token_vector[i]);
		}
		else
		{
			port = ft_atoi(token_vector[i]);
		}
	}
	if (token_vector[++i] != ";")
		return (error("Syntax error : the listen directive doesn't ends by ';'."));
	return (0);
};
