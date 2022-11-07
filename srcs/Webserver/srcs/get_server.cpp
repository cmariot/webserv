#include "Webserver.hpp"

int	Webserver::get_server(void)
{
	for (size_t i = 0 ; i < server.size() ; ++i)
	{
		for (size_t j = 0 ; j < server[i].get_server_names().size() ; ++j)
		{
			if (server[i].get_server_names()[j] == _request._request_address.first
				&& server[i].get_address().second == _request._request_address.second)
			{
				std::cout << "This request will be treated by the server[" << i << "] !" << std::endl;
				return (0);
			}
		}
		if (server[i].get_address() == _request._request_address)
		{
			std::cout << "This request will be treated by the server[" << i << "] !" << std::endl;
			return (0);
		}
	}
	std::cout << "This request will not be treated." << std::endl;
	return (1);
};
