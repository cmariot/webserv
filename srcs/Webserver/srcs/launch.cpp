#include "Webserver.hpp"

bool	Webserver::client_ready(void) const
{
	if ((event.events & EPOLLIN) && (event.events & EPOLLOUT))
		return (true);
	return (false);
};

int	Webserver::treat_client_request(void)
{

	recv_return = recv(event.data.fd, buffer, BUFFER_SIZE - 1, MSG_DONTWAIT);
	if (recv_return == -1)
		return (1);
	buffer[recv_return] = '\0';

	// get current client in the map
	if (recv_return < BUFFER_SIZE - 1)
	{
		std::cout << buffer << std::endl;
		// add buffer to the correct client request
		// send the response
		std::string	response = "HTTP/1.1 200 OK\r\n\r\n<h1>Ca fonctionne !</h1>";
		send(event.data.fd, response.c_str(), response.size(), 0);
		close(event.data.fd);
		print(INFO, "Connexion closed");
	}
	else
	{
		std::cout << buffer << std::endl;
		// add buffer to the correct client request
	}
	return (0);
};

int		Webserver::launch(void)
{
	if (init_sockets())
		return (exit_webserv());
	catch_signal();
	print(INFO, "Waiting for new events ...");
	while (new_events())
	{
		for (int i = 0 ; i < nb_events ; ++i)
		{
			event = events[i];
			if (client_error())
				remove_client();
			else if (client_connection())
				add_client();
			else if (client_ready())
				treat_client_request();
			else
			{
				// Other events ?
			}
		}
	}
	return (exit_webserv());
};
