#include "Webserver.hpp"

# define BUFFER_SIZE 10

int	Webserver::remove_client(const int & client_socket, struct epoll_event *events)
{
	print(INFO, "Closing the client connexion.");
	epoll_ctl(epoll_socket, EPOLL_CTL_DEL, client_socket, events);
	close(client_socket);
	return (0);
};

int		Webserver::client_disconnection(struct epoll_event & event)
{
	if ((event.events & EPOLLERR) || (event.events & EPOLLHUP) || (!(event.events & EPOLLIN)))
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
	while (new_events())
	{
		for (int i = 0 ; i < nb_events ; ++i)
		{
			if (client_disconnection(events[i]))
				continue ;
			else if (client_connection(events[i]))
				continue ;
			else if (events[i].events & EPOLLIN)
			{
				std::cout << "recv : " << request << std::endl;
				bzero(buff, BUFFER_SIZE);
				int	nbbytes = recv(events[i].data.fd, buff, BUFFER_SIZE - 1, 0);
				if (nbbytes < 0)
				{
					if (errno == EAGAIN || errno == EWOULDBLOCK)
						continue ;
					std::cout << "error" << std::endl;
				}
				else if (nbbytes < BUFFER_SIZE - 1)
				{
					std::cout << request << std::endl;
					continue ;
				}
				else
				{
					request += buff;
				}
			}
			else if (events[i].events & EPOLLOUT)
			{
				std::string	response = "HTTP/1.1 200 OK\r\n\r\nOK";
				send(events[i].data.fd, response.c_str(), response.size(), 0);
			}
		}
	}
	exit_webserv();
	return (0);
};
