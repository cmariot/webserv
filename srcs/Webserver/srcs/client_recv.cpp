#include "Webserver.hpp"

int		Webserver::get_request(void)
{
	print(INFO, "Client recv.");
	print(INFO, "Client recv. 2");
	std::map<int, Client>::iterator	it = clients.find(event.data.fd);

	if (it == clients.end())
	{
		close(event.data.fd);
		return (error("Unknow client."));
	}

	Client	client = it->second;

	bzero(buffer, sizeof(char) * BUFFER_SIZE);
	std::cout << "recv_return = ";
	const ssize_t recv_return = recv(event.data.fd, buffer, sizeof(char) * (BUFFER_SIZE - 1), 0);
	std::cout << recv_return << std::endl;
	if (recv_return <= 0)
	{
		if (recv_return == 0)
			print(INFO, "Client connection closed.");
		else
			print(INFO, "Client connection lost.");
		clients.erase(it->first);
		epoll_ctl(epoll_socket, EPOLL_CTL_DEL, event.data.fd, NULL);
		close(event.data.fd);
	}
	else
	{
		buffer[recv_return] = '\0';
		std::cout << buffer << std::endl;
		client._request.request += buffer;
		if (client._request.request.find("\r\n\r\n") != std::string::npos)
		{
			struct epoll_event	new_event;

			bzero(&new_event, sizeof(struct epoll_event));
			new_event.events = EPOLLOUT;
			new_event.data.fd = event.data.fd;
			epoll_ctl(epoll_socket, EPOLL_CTL_MOD, event.data.fd, &new_event);
		}
	}
	return (0);
};

bool	Webserver::client_recv(void)
{
	if (event.events & EPOLLIN)
		return (true);
	return (false);
};
