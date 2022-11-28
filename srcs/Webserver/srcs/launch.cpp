#include "Webserver.hpp"

int		Webserver::launch(void)
{
	if (init_sockets())
		return (exit_webserv());
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
			else if (client_recv()) // read_available
				get_request();
			else if (client_send()) // write_available
				send_response();
		}
	}
	return (exit_webserv());
};
