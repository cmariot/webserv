#include "Response.hpp"

void Response::generate_100_continue(void)
{
	_response  = _request.get_http_version() + " 100 Continue\r\n\r\n";
	return ;
};
