#include "Request.hpp"

bool	Request::is_ready(void)
{
	if (request.find("\r\n\r\n") != std::string::npos)
	{
		interpret();
		if (method == "GET" || method == "DELETE")
			return (true);
		else if (method == "POST")
		{
			// check body_size ?
			return (true);
		}
	}
	return (false);
};
