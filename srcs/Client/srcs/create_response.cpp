#include "Client.hpp"

int	Client::create_response(void)
{
	_response._full_response = "HTTP/1.1 200 OK\r\nContent-Length: 11\r\n\r\n<h1>OK</h1>";
	return (0);
};
