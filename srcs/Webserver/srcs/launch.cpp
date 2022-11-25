#include "Webserver.hpp"

int		Webserver::launch(void)
{
	if (init_sockets())
		return (exit_webserv()); // uninitialised byte(s)
	catch_signal();
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
				handle_client();
			else
			{
				error(strerror(errno));
				close(event.data.fd);
			}
		}
	}
	return (exit_webserv());
};
