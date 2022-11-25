#include "Client.hpp"

int	Client::add_to_request(char *buff)
{
	_request.request += buff;
	return (0);
};
