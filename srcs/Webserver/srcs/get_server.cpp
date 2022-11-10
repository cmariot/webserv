#include "Webserver.hpp"

// Trouve le serveur (parmi ceux presents dans notre vecteur de serveur) sur lequel la requete a ete envoyee.
// C'est le server[i] qui sera utilise pour la generation de la reponse.
int	Webserver::get_server(Server & request_server)
{
	for (size_t i = 0 ; i < server.size() ; ++i)
	{
		if ((server[i].get_server_names().count(_request.request_address.first) == 1
				&& server[i].get_address().second == _request.request_address.second)
			|| server[i].get_address() == _request.request_address)
		{
			print(INFO, ("This request will be treated by the server[" + itostring(i) + "] !").c_str());
			request_server = server[i];
			return (0);
		}
	}
	print(INFO, "Unable to find the server.");
	request_server = Server();
	return (1);
};
