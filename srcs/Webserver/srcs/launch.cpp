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
			else if (client_recv() == READY)
				get_request();
			else if (client_send() == READY)
				send_response();
		}
		//std::cout << "Number of events  = " << nb_events << std::endl;
		//std::cout << "Number of clients = " << clients.size() << std::endl;
	}
	return (exit_webserv());
};
