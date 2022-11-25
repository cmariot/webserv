#include "Client.hpp"

Client::Client(const int & socket, const Server & server) :
	_socket(socket),
	_server(server)
{
	print(INFO, "New client !");
	return ;
};
