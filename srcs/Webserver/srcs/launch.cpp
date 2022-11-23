#include "Webserver.hpp"

int		Webserver::launch(char *const *env)
{
	(void)env;

	// Ouvrir un epoll_socket avec epoll create
	// A FAIRE ICI

	// Pour chaque serveur : 
	for (size_t i = 0 ; i < nb_of_servers ; ++i)
	{
		// Ouvrir un socket
		server[i].socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (server[i].socket == -1)
			std::cerr << "socket" << std::endl;

		// Attribuer un type, un host et un port a l'addresse de ce socket
		server[i].address.sin_family = AF_INET;
		server[i].address.sin_addr.s_addr = inet_addr(server[i].get_address().first.c_str());
		server[i].address.sin_port = htons(server[i].get_address().second);

		// Bind socket et addresse
		if (bind(server[i].socket, (const sockaddr *)&server[i].address, sizeof(server[i].address)) == -1)
			std::cerr << "bind" << std::endl;

		// Listen
		// fcntl pour non-bloquant ici ?
	}

	// Ajouter chaque server_socket a epoll_socket
	// Signal catcher
	// Boucle infinie
	// Close
	return (0);
};
