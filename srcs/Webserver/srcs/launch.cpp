#include "Webserver.hpp"

# define BUFFER_SIZE 50

void	Webserver::remove_client(void)
{
	print(INFO, "Closing the client connexion.");
	close(event.data.fd);
};

bool	Webserver::client_ready(void) const
{
	if ((event.events & EPOLLIN) && (event.events & EPOLLOUT))
		return (true);
	return (false);
};

bool	Webserver::client_error(void) const
{
	if ((event.events & EPOLLERR) || (event.events & EPOLLHUP))
		return (true);
	return (false);
};

int		Webserver::launch(void)
{
	char		buff[BUFFER_SIZE];
	// create a map of client <fd, client>

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
			{
				// add client to the map
				std::cout << "New connection." << std::endl;
			}
			else if (client_ready())
			{
				bzero(buff, BUFFER_SIZE);
				ssize_t recv_return = recv(event.data.fd, buff, BUFFER_SIZE - 1, MSG_DONTWAIT);
				if (recv_return == -1)
					continue ;
				// get current client in the map
				if (recv_return < BUFFER_SIZE - 1)
				{
					std::cout << buff << std::endl;
					// add buff to the correct client request
					// send the response
					std::string	response = "HTTP/1.1 200 OK\r\n\r\n<h1>Ca fonctionne !</h1>";
					send(event.data.fd, response.c_str(), response.size(), 0);
					close(event.data.fd);
					print(INFO, "Connexion closed");
				}
				else
				{
					std::cout << buff << std::endl;
					// add buff to the correct client request
				}
			}
			else
			{
				// Other events ?
			}
		}
	}
	return (exit_webserv());
};
