#include "Webserver.hpp"

size_t Webserver::nb_of_servers = 0;

Webserver::Webserver(void) :
	main_socket(0)
{
	return ;
};
