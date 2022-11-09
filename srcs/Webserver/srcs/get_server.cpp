#include "Webserver.hpp"

// Trouve le serveur (parmi ceux presents dans notre vecteur de serveur) sur lequel la requete a ete envoyee.
// C'est le server[i] qui sera utilise pour la generation de la reponse.
int	Webserver::get_server(Server & request_server)
{
	for (size_t i = 0 ; i < server.size() ; ++i)
	{
		for (size_t j = 0 ; j < server[i].get_server_names().size() ; ++j)
		{
			if (server[i].get_server_names()[j] == _request.request_address.first
				&& server[i].get_address().second == _request.request_address.second)
			{
				std::cout << "This request will be treated by the server[" << i << "] !" << std::endl;
				request_server = server[i];
				return (0);
			}
		}
		if (server[i].get_address() == _request.request_address)
		{
			std::cout << "This request will be treated by the server[" << i << "] !" << std::endl;
			request_server = server[i];
			return (0);
		}
	}
	request_server = Server();
	return (1);
};
