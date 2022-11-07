#include "Webserver.hpp"

// Parser /etc/hosts ??

int	Webserver::get_server(void)
{
	std::string	uri;

	size_t	pos = _request._host.find(":"); // gestion d'erreur a faire ici, voir les cas + en detail pour comparaison host avec server_names et/ou address
	if (pos != std::string::npos)
		uri = _request._host.substr(0, pos);
	else
		uri = _request._host;
	for (size_t i = 0 ; i < server.size() ; ++i)
	{
		for (size_t j = 0 ; j < server[i].get_server_names().size() ; ++j)
		{
			if (server[i].get_server_names()[j] == uri)
			{
				std::cout << "This request will be used by the server[" << i << "] !" << std::endl;
				return (0);
			}
		}
		if (server[i].get_address() == _request._request_address)
		{
			std::cout << "This request will be used by the server[" << i << "] !" << std::endl;
			return (0);
		}
	}
	return (1);
};
