#include "Webserver.hpp"

int	Webserver::handle_client(void)
{
	recv_return = recv(event.data.fd, buffer, BUFFER_SIZE - 1, MSG_DONTWAIT);
	if (recv_return == -1)
		return (1);
	buffer[recv_return] = '\0';

	// get current client in the map
	if (recv_return < BUFFER_SIZE - 1)
	{
		std::cout << buffer;
		// add buffer to the correct client request
		// send the response
		std::string	response = "HTTP/1.1 200 OK\r\n\r\n<h1>Ca fonctionne !</h1>";
		send(event.data.fd, response.c_str(), response.size(), 0);
		close(event.data.fd);
		print(INFO, "Connexion closed");
	}
	else
	{
		std::cout << buffer;
		// add buffer to the correct client request
	}
	return (0);
};

bool	Webserver::client_ready(void) const
{
	if ((event.events & EPOLLIN) && (event.events & EPOLLOUT))
		return (true);
	return (false);
};
