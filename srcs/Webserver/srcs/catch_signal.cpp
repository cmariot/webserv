#include "Webserver.hpp"

static void	sigint_primitive(int signal)
{
	print(INFO, "Signal caught, bye.");
	(void)signal;
};

int		Webserver::catch_signal(void)
{
	struct sigaction	ctrl_c_primitive;

	bzero(&ctrl_c_primitive, sizeof(ctrl_c_primitive));
	ctrl_c_primitive.sa_handler = &sigint_primitive;
	sigaction(SIGINT, &ctrl_c_primitive, 0);
	print(INFO, "Waiting for new events ...");
	return (0);
};
