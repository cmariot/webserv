#include "Client.hpp"

int	Client::add_to_request(char *buff, const ssize_t & recv_return)
{
	_request.add_to_request(buff, recv_return);
	return (0);
};
