#include "Client.hpp"

int	Client::add_to_request(char *buff)
{
	_request.add_to_request(buff);
	return (0);
};
