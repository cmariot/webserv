#include "Utils.hpp"

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

std::string	set_ip(std::string ip)
{
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
		size_t	i = 0;

		while (i < ip.size())
		{
			while (i < ip.size() && ip[i] >= '0' && ip[i] <= '9')
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

