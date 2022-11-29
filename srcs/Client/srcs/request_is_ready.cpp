#include "Client.hpp"

bool	Client::request_is_ready(void)
{
	static bool	body_complete = false;

	_request.interpret();
	if (_request.request.find("\r\n\r\n") != std::string::npos)
	{
		_request.interpret();
		if (_request.method == "GET" || _request.method == "DELETE")
			return (true);
		else if (_request.method == "POST")
		{
			// Check post a revoir ? On attend la fin du body ?
			if (_request.request.rfind("\0") != std::string::npos)
				body_complete = true;
			return (body_complete);
		}
	}
	return (false);
};
