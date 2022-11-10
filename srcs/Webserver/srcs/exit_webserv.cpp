#include "Webserver.hpp"

int	Webserver::exit_webserv(void)
{
	close(main_socket);
	for (size_t i = 0 ; i < nb_of_servers ; ++i)
		close(server[i]._server_socket);
	close(STDIN);
	close(STDOUT);
	close(STDERR);
	return (1);
};
