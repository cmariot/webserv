#include "Response.hpp"

void	Response::update(Request & request, Server & server)
{
	_request = request;
	_server = server;
};
