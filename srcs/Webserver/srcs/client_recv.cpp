#include "Webserver.hpp"

int		Webserver::get_request(void)
{
	std::map<int, Client>::iterator	it = clients.find(event.data.fd);

	if (it == clients.end())
	{
		epoll_ctl(epoll_socket, EPOLL_CTL_DEL, event.data.fd, 0);
		close(event.data.fd);
		return (error("Unknow client."));
	}

	Client	& client = it->second;

	bzero(buffer, sizeof(char) * BUFFER_SIZE);

	const ssize_t recv_return = recv(it->first,
							buffer,
							sizeof(char) * (BUFFER_SIZE - 1),
							O_NONBLOCK);

	if (recv_return <= 0)
	{
		if (recv_return == 0)
			print(INFO, "Client connection closed.");
		else
			print(INFO, "Client connection lost.");
		remove_client();
	}
	else
	{
		print(INFO, "Server received data from client.");
		buffer[recv_return] = '\0';
		client.add_to_request(buffer, recv_return);
		if (client.request_is_ready())
		{
			struct epoll_event	new_event;

			bzero(&new_event, sizeof(struct epoll_event));
			new_event.data.fd = it->first;
			new_event.events = EPOLLOUT;
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
