#include "Response.hpp"
#include <unistd.h>
#include <stdio.h>

#define NUM_PIPES          2
 
#define PARENT_WRITE_PIPE  0
#define PARENT_READ_PIPE   1
#define READ_FD  0
#define WRITE_FD 1
 
#define PARENT_READ_FD  ( pipes[PARENT_READ_PIPE][READ_FD]   )
#define PARENT_WRITE_FD ( pipes[PARENT_WRITE_PIPE][WRITE_FD] )
 
#define CHILD_READ_FD   ( pipes[PARENT_WRITE_PIPE][READ_FD]  )
#define CHILD_WRITE_FD  ( pipes[PARENT_READ_PIPE][WRITE_FD]  )

bool Response::execute_script(char **arg)
{
	execve(arg[0], arg, get_env());
	return (0);
};

char *const *Response::get_env(void)
{
    return (_env);
};

# define BUFFER_SIZE 1024

int Response::build_cgi_response(string & path)
{
    int	pid;
	char *arg[3];
	int pipes[NUM_PIPES][2];

	pipe(pipes[PARENT_READ_PIPE]);
    pipe(pipes[PARENT_WRITE_PIPE]);

    pid = fork();
	if (pid == -1)
		return (error("Fork failed."));
	else if (pid == 0)
	{
		arg[0] = strdup("/bin/php-cgi");
		arg[1] = strdup(path.c_str());
		arg[2] = NULL; 
		dup2(CHILD_READ_FD, STDIN_FILENO);
		dup2(CHILD_WRITE_FD, STDOUT_FILENO);
		close(CHILD_READ_FD);
        close(CHILD_WRITE_FD);
        close(PARENT_READ_FD);
        close(PARENT_WRITE_FD);
		if (execute_script(arg))
			return (0);
	}
	else
	{
		char	buffer[BUFFER_SIZE];
		size_t	count = BUFFER_SIZE;

		close(CHILD_READ_FD);
		close(CHILD_WRITE_FD);
		_response_body = "";
		while (true)
		{
			bzero(buffer, count);
			count = read(PARENT_READ_FD, buffer, BUFFER_SIZE - 1);
			buffer[count] = 0;
			if (count == 0)
				break ;
			_response_body += buffer;
		}
		const std::string	code = "200";
		const std::string	message = _status_code_map.find(200)->second;
		_status_code = 200;
		_response_header = _request.http_version + " " + code + " " + message + "\r\n\r\n";
		_response_body = _response_body.substr(39, _response_body.size());
		_full_response = _response_header + _response_body;
	}
	return (0);
};
