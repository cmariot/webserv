#include "Webserver.hpp"

// Trouve le serveur (parmi ceux presents dans notre vecteur de serveur) sur lequel la requete a ete envoyee.
// C'est le server[i] qui sera utilise pour la generation de la reponse.
int	Webserver::get_server(Client & client)
{
	for (size_t i = 0 ; i < servers.size() ; ++i)
	{
		if ((servers[i].get_server_names().count(client._request.request_address.first) == 1
				&& servers[i].get_address().second == client._request.request_address.second)
			|| servers[i].get_address() == client._request.request_address)
		{
			client._server = servers[i];
			return (0);
		}
	}
	client._server = Server();
	return (error("A client has a incorrect server."));
};

int		Webserver::send_response(void)
{
	std::map<int, Client>::iterator	it = clients.find(event.data.fd);

	if (it == clients.end())
	{
		close(event.data.fd);
		return (error("Unknow client."));
	}

	Client	& client = it->second;

	client._request.interpret();
	if (get_server(client))
	{
		//return 404
		remove_client();
		return (false);
	}
	client._response.update(client._request, client._server, get_env());
	client._response.create();
	client._request.request.clear();

	const ssize_t send_return = send(it->first,
					client._response._full_response.c_str(),
					client._response._full_response.size(),
					O_NONBLOCK);

	if (send_return <= 0)
	{
		if (send_return == 0)
			print(INFO, "Send returned 0.");
		else
			print(INFO, "Send error.");
		clients.erase(it->first);
		epoll_ctl(epoll_socket, EPOLL_CTL_DEL, event.data.fd, 0);
		close(event.data.fd);
		return (1);
	}
	else
	{
		print(INFO, "The server is sending a response to the client.");
		struct epoll_event	new_event;

		bzero(&new_event, sizeof(struct epoll_event));
		new_event.data.fd = it->first;
		new_event.events = EPOLLIN;
		epoll_ctl(epoll_socket, EPOLL_CTL_MOD, event.data.fd, &new_event);
	}
	return (0);
};

bool	Webserver::client_send(void)
{
	if (event.events & EPOLLOUT)
		return (true);
	return (false);
};
