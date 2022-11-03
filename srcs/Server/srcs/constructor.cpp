#include "Server.hpp"

Server::Server(void) :
	_address(std::make_pair<std::string, size_t>("", 0)),
	_client_max_body_size(0)
{
	return ;
};
