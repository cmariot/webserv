#include "Server.hpp"

Server::Server(void) :
	_address(std::make_pair<std::string, size_t>("0.0.0.0", 8080)),
	_client_max_body_size(0),
	address_set(false),
	server_names_set(false),
	client_max_body_size_set(false),
	error_page_set(false),
	locations_set(false),
	socket(0),
	addrlen(sizeof(struct sockaddr_in))
{
	return ;
};
