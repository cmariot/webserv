#include "Webserver.hpp"

int		Webserver::init_sockets(void)
{
	std::string str;

	print(INFO, "Opening the sockets for the servers communication.");
	if (create_main_socket())
		return (1);
	for (size_t i = 0 ; i < nb_of_servers ; ++i)
	{
		if (server[i].create_server_socket())
			return (1);
		if (server[i].bind_server_address())
			return (1);
		if (server[i].listen_for_clients())
			return (1);
		if (add_to_interest_list(&server[i]))
			return (1);
		str = "Server ";
		str += itostring(i);
		str += " is listening on ";
		str += server[i].get_address().first;
		str += ":";
		str += itostring(static_cast<int>(server[i].get_address().second));
		print(INFO, str.c_str());
	}
	return (0);
};
