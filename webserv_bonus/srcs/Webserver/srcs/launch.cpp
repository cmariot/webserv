#include "Webserver.hpp"

int		Webserver::launch(void)
{
	if (init_sockets())
		return (exit_webserv());
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
			else if (client_recv() == READY)
				get_request();
			else if (client_send() == READY)
				send_response();
		}
	}
	return (exit_webserv());
};
