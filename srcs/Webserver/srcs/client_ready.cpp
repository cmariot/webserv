#include "Webserver.hpp"

bool	Webserver::create_response(Client & client)
{
	client.add_to_request(buffer);
	client._request.interpret();
	client._response.update(client._request, client._server, get_env());
	client._response.create(event.data.fd);
	clients.erase(event.data.fd);
	close(event.data.fd);
	print(INFO, "Connexion closed");
	return (true);
};

# define FAIL 1

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
	{
		close(event.data.fd);
		return (1);
	}
	buffer[recv_return] = '\0';
	return (0);
};

static int	join_request(Client & client, char *buffer)
{
	client.add_to_request(buffer);
	return (0);
};

int	Webserver::handle_client(void)
{
	std::map<const int, Client>::iterator	client = clients.find(event.data.fd);

	if (client == clients.end())
	{
		error("Unkwown client socket.");
		close(event.data.fd);
		return (1);
	}
	if (receive_input() == FAIL)
		return (1);
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
