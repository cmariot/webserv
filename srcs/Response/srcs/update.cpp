#include "Response.hpp"

void	Response::update(Request & request, Server & server)
{
	_request = request;
	_server = server;
	_location = Location();
	_response_header.clear();
	_response_body.clear();
	_full_response.clear();
};
