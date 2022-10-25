#include "Webserver.hpp"

void	sigint_primitive(int signal)
{
	(void)signal;
	std::cout << "\rSIGINT signal catched." << std::endl;
}

int		Webserver::catch_signal(void)
{
	struct sigaction	ctrl_c_primitive;

	bzero(&ctrl_c_primitive, sizeof(ctrl_c_primitive));
	ctrl_c_primitive.sa_handler = &sigint_primitive;
	sigaction(SIGINT, &ctrl_c_primitive, 0);
	return (0);
}
