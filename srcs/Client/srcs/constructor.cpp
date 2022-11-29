#include "Client.hpp"

Client::Client(const int & socket) :
	_socket(socket)
{
	_server = Server();
	_request = Request();
	std::cout << "Client socket = " << socket << std::endl; 
	return ;
};
