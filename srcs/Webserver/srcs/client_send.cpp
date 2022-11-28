#include "Webserver.hpp"

int		Webserver::send_response(void)
{
	print(INFO, "Client send.");
	std::map<int, Client>::iterator	it = clients.find(event.data.fd);

	if (it == clients.end())
	{
		close(event.data.fd);
		return (error("Unknow client."));
	}

	Client	client = it->second;

	client._response._full_response = "HTTP/1.1 200 OK\r\n\r\n<h1>OK</h1>";

	const ssize_t send_return = send(event.data.fd,
					client._response._full_response.c_str(),
					client._response._full_response.size(),
					0);
	if (send_return <= 0)
	{
		print(INFO, "Send error.");
		clients.erase(it->first);
		epoll_ctl(epoll_socket, EPOLL_CTL_DEL, event.data.fd, 0);
		close(event.data.fd);
		return (1);
	}
	else
	{
		print(INFO, "Mod event.");
		struct epoll_event	new_event;

		bzero(&new_event, sizeof(struct epoll_event));
		new_event.events = EPOLLIN;
		new_event.data.fd = it->first;
		if (epoll_ctl(epoll_socket, EPOLL_CTL_ADD, it->first, &new_event) != 0)
			return (error(strerror(errno)));
	}
	return (0);
};

bool	Webserver::client_send(void)
{
	if (event.events & EPOLLOUT)
		return (true);
	return (false);
};
