#include "Webserver.hpp"

size_t Webserver::nb_of_servers = 0;

Webserver::Webserver(void) :
	nb_events(0)
{
	return ;
};
