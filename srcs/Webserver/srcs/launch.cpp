#include "Webserver.hpp"

# define BUFFER_SIZE 50

int	Webserver::remove_client(const int & client_socket, struct epoll_event *events)
{
	print(INFO, "Closing the client connexion.");
	epoll_ctl(epoll_socket, EPOLL_CTL_DEL, client_socket, events);
	close(client_socket);
	return (0);
};

int		Webserver::client_disconnection(struct epoll_event & event)
{
	if ((event.events & EPOLLERR) || (event.events & EPOLLHUP))
	{
		std::cout << "client_disconnection" << std::endl;
		epoll_ctl(epoll_socket, EPOLL_CTL_DEL, event.data.fd, events);
		close(event.data.fd);
		return (true);
	}
	return (false);
};

int		Webserver::launch(void)
{
	char		buff[BUFFER_SIZE];
	std::string	request;

	if (init_sockets())
		return (1);
	catch_signal();
	std::cout << "Waiting events ..." << std::endl;
	while (new_events())
	{
		std::cout << nb_events << " events to treat." << std::endl;
		for (int i = 0 ; i < nb_events ; ++i)
		{
			if (client_disconnection(events[i]))
			{
				std::cout << "Disconnection." << std::endl;
				continue ; // remove from ready_list
			}
			else if (client_connection(events[i]))
			{
				std::cout << "New connection." << std::endl;
				continue ; // add to ready_list
			}
			else if (events[i].events & EPOLLIN)
			{
				std::cout << "Read data" << std::endl;
				bzero(buff, BUFFER_SIZE);
				ssize_t recv_return = recv(events[i].data.fd, buff, BUFFER_SIZE - 1, 0);
				if (recv_return == -1)
				{
					std::cout << 1 << std::endl;
					if (errno == EAGAIN || errno == EWOULDBLOCK)
					{
						close(events[i].data.fd);
					}
				}
				else if (recv_return < BUFFER_SIZE - 1)
				{
					std::cout << 2 << std::endl;
					std::cout << "close" << std::endl;
					std::string	response = "HTTP:1 200 OK\r\n\r\nCa fonctionne !";
					send(events[i].data.fd, response.c_str(), response.size(), 0);
					close(events[i].data.fd);
					continue ;
				}
				else
				{
					std::cout << 3 << std::endl;
					std::cout << buff << std::endl;
				}
			}
		}
	}
	exit_webserv();
	return (0);
};
