#include "Webserver.hpp"

void	Webserver::remove_client(void)
{
	print(INFO, "Closing the client connexion.");
	clients.erase(event.data.fd);
	close(event.data.fd);
};

bool	Webserver::client_error(void) const
{
	if ((event.events & EPOLLERR) || (event.events & EPOLLHUP))
		return (true);
	return (false);
};
