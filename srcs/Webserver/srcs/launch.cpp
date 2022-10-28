#include "Webserver.hpp"

#define SIGNAL_CAUGHT nb_events == -2

#define INFO	0
#define ERROR	1
#define DEBUG	2

void display(int level, std::string message)
{
	if (level == INFO)
		std::cout << "[webserv:info] : "; 
	else if (level == ERROR)
		std::cout << "[webserv:debug] : "; 
	else if (level == DEBUG)
		std::cout << "[webserv:debug] : "; 
	std::cout << message << std::endl;
	return ;
};

int		Webserver::launch(void)
{
	ssize_t				nb_events;
	struct epoll_event	events[MAX_EVENTS];
	int					client_socket;
	ssize_t				index;
	
	if (init_sockets())
		return (exit_webserv());
	catch_signal();
	display(INFO, "Waiting for new events ..."); 
	while (true)
	{
		nb_events = wait_event(events);
		if (SIGNAL_CAUGHT || nb_events == -1)
			return (exit_webserv());
		for (ssize_t i = 0 ; i < nb_events ; ++i)
		{
			if (client_connexion(&index, events[i]))
			{
				std::cout << "A client has just connected to the server " << server[index].ip << ":" << server[index].port << std::endl;
				if (accept_connexion(&client_socket, server[index]))
					return (exit_webserv());
				if (add_client(client_socket, events))
					return (exit_webserv());
			}
			// else if client disconnect
			//		remove client
			else
			{
				//std::cout << "Event traitment" << std::endl;
				char request[1024];
				memset(request, 0, 1024);
				recv(events[i].data.fd, request, 1024, 0);
				//std::cout << request;

				if (server_response(events[i].data.fd, request))
				{
					std::cout << "response failure" << std::endl;
					return (exit_webserv());
				}

				if (remove_client(epoll_socket, client_socket, events))
					return (exit_webserv());
			}
		}
	}
	return (0);
};
