#include "Response.hpp"

void	Response::update(Request & request, Server & server, char * const *env)
{
	_request = request;
	_server = server;
	_env = env;
	_response.clear();
};
