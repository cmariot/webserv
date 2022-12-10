#include "Request.hpp"

void	Request::clear(void)
{
	_request.clear();
};

void	Request::add_to_request(const char * buffer, const ssize_t & recv_return)
{
	_request.append(buffer, recv_return);
};
