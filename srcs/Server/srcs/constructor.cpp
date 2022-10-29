#include "Server.hpp"

Server::Server(void) :
	address(std::make_pair<std::string, size_t>("", 0)),
	client_max_body_size(0)
{
	return ;
};
