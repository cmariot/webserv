#include "Response.hpp"

void Response::generate_100_continue(void)
{
	_header  = _request.get_http_version() + "100 Continue\r\n\r\n";
	_response = _header;
	return ;
};