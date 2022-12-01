#include "Webserver.hpp"

static void	sigint_primitive(int signal)
{
	(void)signal;
	print(INFO, "Signal caught, bye.");
};

int	Webserver::catch_signal(void)
{
	struct sigaction	ctrl_c_primitive;
	struct sigaction	ctrl_backslash_primitive;

	bzero(&ctrl_c_primitive, sizeof(ctrl_c_primitive));
	ctrl_c_primitive.sa_handler = &sigint_primitive;
	if (sigaction(SIGINT, &ctrl_c_primitive, 0) == -1)
		return (error(strerror(errno)));
	bzero(&ctrl_backslash_primitive, sizeof(ctrl_backslash_primitive));
	ctrl_backslash_primitive.sa_handler = &sigint_primitive;
	if (sigaction(SIGQUIT, &ctrl_c_primitive, 0) == -1)
		return (error(strerror(errno)));
	return (0);
};
