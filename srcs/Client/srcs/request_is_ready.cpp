#include "Client.hpp"

bool	Client::request_is_ready(void)
{
	if (_request.request.find("\r\n\r\n") != std::string::npos)
	{
		_request.interpret();
		if (_request.method == "GET" || _request.method == "DELETE")
			return (true);
		else if (_request.method == "POST")
		{
			// check body_size ?
			return (true);
		}
	}
	return (false);
};
