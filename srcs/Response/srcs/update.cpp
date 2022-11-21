#include "Response.hpp"

void	Response::update(Request & request, Server & server, char *const *env)
{
	_request = request;
	_server = server;
	_env = env;
	_location = Location();
	_response_header.clear();
	_response_body.clear();
	_full_response.clear();
};
