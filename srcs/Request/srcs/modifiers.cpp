#include "Request.hpp"

void	Request::clear(void)
{
	_request.clear();
	_header_is_ready = false;
	_body_is_ready = false;
};

void	Request::add_to_request(const char * buffer)
{
	_request += buffer;
};
