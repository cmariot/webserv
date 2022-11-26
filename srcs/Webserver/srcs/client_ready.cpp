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

bool	Webserver::create_response(Client & client)
{
	client.add_to_request(buffer);
	client._request.interpret();
	if (get_server(client))
	{
		//return 404
		return (false);
	}
	client._response.update(client._request, client._server, get_env());
	client._response.create();
	client._request.request.clear();
	print(INFO, "Sending response.");
	send(event.data.fd, client._response._full_response.c_str(), client._response._full_response.size(), 0);
	print(INFO, "Closing client connexion.");
	clients.erase(event.data.fd);
	close(event.data.fd);
	return (true);
};

static int	join_request(Client & client, char *buffer)
{
	client.add_to_request(buffer);
	return (0);
};

static bool	incomplete_request(const ssize_t & recv_return)
{
	const ssize_t	max_size = BUFFER_SIZE - 1;
	if (recv_return == max_size)
		return (true);
	return (false);
};

int	Webserver::receive_input(void)
{
	recv_return = recv(event.data.fd, buffer, BUFFER_SIZE - 1, MSG_DONTWAIT);
	if (recv_return == -1)
		return (1);
	buffer[recv_return] = '\0';
	return (0);
};

# define FAIL 1

int	Webserver::handle_client(void)
{
	std::map<const int, Client>::iterator	client = clients.find(event.data.fd);

	print(INFO, "Receive data");
	if (client == clients.end())
		return (error("Unkwown client socket."));
	if (receive_input() == FAIL)
		return (error("recv failed"));
	if (incomplete_request(recv_return))
		join_request(client->second, buffer);
	else
		create_response(client->second);
	return (0);
};

bool	Webserver::client_ready(void) const
{
	if ((event.events & EPOLLIN) && (event.events & EPOLLOUT))
		return (true);
	return (false);
};
