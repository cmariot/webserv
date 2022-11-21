#include "Response.hpp"

bool Response::execute_script(char **arg)
{
	execve(arg[0], arg, get_env());
	return (0);
};

char *const *Response::get_env(void)
{
    return (_env);
};

int Response::build_cgi_response(string & path)
{
    std::cout << path << std::endl;
    int	pid;
	char *(arg[3]);

    arg[0] = strdup("/usr/bin/php");
    arg[1] = strdup(path.c_str());
    arg[2] = NULL; 
    pid = fork();
	if (pid == 0)
		if (execute_script(arg))
			return (0);
    waitpid(pid, NULL, 0);
    free(arg[0]);
    free(arg[1]);
	return (1);
};
