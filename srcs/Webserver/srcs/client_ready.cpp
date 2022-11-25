#include "Webserver.hpp"

int	Webserver::handle_client(void)
{
	std::map<const int, Client>::iterator	client = clients.find(event.data.fd);
	if (client == clients.end())
	{
		error("Unkwown client socket.");
		close(event.data.fd);
		return (0);
	}
	recv_return = recv(event.data.fd, buffer, BUFFER_SIZE - 1, MSG_DONTWAIT);
	if (recv_return == -1)
		return (1);
	buffer[recv_return] = '\0';
	if (recv_return < BUFFER_SIZE - 1)
	{
		client->second.add_to_request(buffer);
		client->second._request.interpret();
		client->second._response.update(client->second._request, client->second._server, get_env());
		client->second._response.create(event.data.fd);
		clients.erase(event.data.fd);
		close(event.data.fd);
		print(INFO, "Connexion closed");
	}
	else
		client->second.add_to_request(buffer);
	return (0);
};

bool	Webserver::client_ready(void) const
{
	if ((event.events & EPOLLIN) && (event.events & EPOLLOUT))
		return (true);
	return (false);
};
