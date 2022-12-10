#include "Webserver.hpp"

int		Webserver::send_response(void)
{
	std::map<int, Client>::iterator	it = clients.find(event.data.fd);

	if (it == clients.end())
	{
		close(event.data.fd);
		return (error("Unknow client."));
	}

	Client	& client = it->second;

	client.create_response(servers, get_env());

	print(INFO, "Response :");
	std::cout << client.get_response() << std::endl;

	const ssize_t send_return = send(it->first,
					client.get_response(),
					client.get_response_size(),
					O_NONBLOCK);

	if (send_return <= 0)
	{
		if (send_return == 0)
			print(INFO, "Send returned 0.");
		else
			print(INFO, "Send error.");
		remove_client();
		return (1);
	}
	else
	{
		print(INFO, "The response has been send.");

		struct epoll_event	new_event;

		bzero(&new_event, sizeof(struct epoll_event));
		new_event.data.fd = it->first;
		new_event.events = EPOLLIN;
		if (epoll_ctl(epoll_socket, EPOLL_CTL_MOD, event.data.fd, &new_event) == -1)
			error("Epoll_ctl MOD failed.");
	}
	return (0);
};

bool	Webserver::client_send(void)
{
	if (event.events & EPOLLOUT)
		return (true);
	return (false);
};
