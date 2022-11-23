#include "Webserver.hpp"

# define BUFFER_SIZE 4096

int		Webserver::launch(void)
{
	size_t	server_index;
	int		client_socket;

	if (init_sockets())
		return (1);
	catch_signal();
	while (true)
	{
		if (wait_event() == SIGNAL_CAUGHT)
			break ;
		for (int i = 0 ; i < nb_events ; i++)
		{
			if (client_connexion(server_index, events[i]))
			{
				if (accept_connexion(client_socket, server[server_index], events))
					std::cerr << "accept_connexion" << std::endl;
				continue ;
			}
			else
			{
				char	buff[BUFFER_SIZE];
				bzero(buff, BUFFER_SIZE);
				recv(events[i].data.fd, buff, BUFFER_SIZE - 1, 0);
				std::cout << buff << std::endl;

				std::cout << "PTR = " << (events[i].data.ptr) << std::endl;
				std::cout << "MAIN = " << &main_socket << std::endl;
			}
		}
	}
	exit_webserv();
	return (0);
};
