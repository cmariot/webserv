#include "Webserver.hpp"

# define BUFFER_SIZE 50

int	Webserver::remove_client(const int & client_socket, struct epoll_event *events)
{
	print(INFO, "Closing the client connexion.");
	epoll_ctl(epoll_socket, EPOLL_CTL_DEL, client_socket, events);
	close(client_socket);
	return (0);
};

int		Webserver::launch(void)
{
	if (init_sockets())
		return (1);
	catch_signal();
	while (new_events()) // verifs
	{
		for (int i = 0 ; i < nb_events ; ++i)
		{
			if (client_connexion(events[i]))
				continue ;
			else if (events[i].events & EPOLLIN)
			{
				char	buff[BUFFER_SIZE];

				bzero(buff, BUFFER_SIZE);
				recv(events[i].data.fd, buff, BUFFER_SIZE - 1, 0);
				std::cout << buff << std::endl;
			}
		}
	}
	exit_webserv();
	return (0);
};
