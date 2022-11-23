#include "Webserver.hpp"

int		Webserver::init_sockets(void)
{
	// Ouvrir un epoll_socket avec epoll create
	main_socket = epoll_create1(0);
	if (main_socket == -1)
		std::cerr << "epoll_create1" << std::endl;

	// Pour chaque serveur : 
	for (size_t i = 0 ; i < nb_of_servers ; ++i)
	{
		// Ouvrir un socket
		server[i].socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (server[i].socket == -1)
			std::cerr << "socket" << std::endl;

		//setsockopt ?
		const int		options			= 1;
		const void *	option_value	= &options;
		const socklen_t	option_len		= sizeof(options);

		if (setsockopt(server[i].socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, option_value, option_len) == -1)
			std::cerr << "setsockopt" << std::endl;

		// Attribuer un type, un host et un port a l'addresse de ce socket
		server[i].address.sin_family = AF_INET;
		server[i].address.sin_addr.s_addr = inet_addr(server[i].get_address().first.c_str());
		server[i].address.sin_port = htons(server[i].get_address().second);

		// Bind socket et addresse
		if (bind(server[i].socket, (const sockaddr *)&(server[i].address), sizeof(server[i].address)) == -1)
			std::cerr << "bind" << std::endl;

		// Listen
		if (listen(server[i].socket, 42) == -1)
			std::cerr << "listen" << std::endl;

		// Options du server_socket
		bzero(&event, sizeof(event));
		event.data.fd = server[i].socket;
		event.events = EPOLLIN | EPOLLOUT | EPOLLET;

		// Non-blocking socket
		if (fcntl(server[i].socket, F_SETFL, O_NONBLOCK) == -1)
			std::cerr << "fcntl" << std::endl;

		// Ajout a la liste d'interet
		if (epoll_ctl(main_socket, EPOLL_CTL_ADD, server[i].socket, &event) == -1)
			std::cerr << "epoll_ctl" << std::endl;
	}
	return (0);
};
