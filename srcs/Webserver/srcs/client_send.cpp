#include "Webserver.hpp"

// Trouve le serveur (parmi ceux presents dans notre vecteur de serveur) sur lequel la requete a ete envoyee.
// C'est le server[i] qui sera utilise pour la generation de la reponse.
int	Webserver::get_server(Client & client)
{
	for (size_t i = 0 ; i < servers.size() ; ++i)
	{
		if ((servers[i].get_server_names().count(client.get_hostname()) == 1
				&& servers[i].get_address().second == client.get_port())
			|| servers[i].get_address() == client.get_address())
		{
			client.set_server(servers[i]);
			return (0);
		}
	}
	client.set_server(Server());
	return (error("A client has an incorrect server."));
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

	client.create_response();

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
