#include "Response.hpp"
#include <sys/wait.h>
#include <cstdlib>

# define NUM_PIPES			2

# define PARENT_WRITE_PIPE	0
# define PARENT_READ_PIPE	1

# define READ_FD			0
# define WRITE_FD			1

# define PARENT_WRITE_FD	( pipes[PARENT_WRITE_PIPE][WRITE_FD] )
# define PARENT_READ_FD		( pipes[PARENT_READ_PIPE][READ_FD]   )

# define CHILD_WRITE_FD		( pipes[PARENT_READ_PIPE][WRITE_FD]  )
# define CHILD_READ_FD		( pipes[PARENT_WRITE_PIPE][READ_FD]  )

int Response::generate_cgi_response(void)
{
    int		pid;
	char	*cgi_args[3];
	int		pipes[NUM_PIPES][2];
	std::string	full_path;

	_body.clear();

	// Full path as PATH_INFO
	if (_path.empty() == false && _path[0] != '/')
	{
		char	*pwd = getcwd(NULL, 0);

		if (pwd == NULL)
			return (error("getcwd() failed"));
		full_path = pwd + std::string("/") + _path;
		free(pwd);
	}
	else
		full_path = _path;

	if (pipe(pipes[PARENT_READ_PIPE]) == -1
		|| pipe(pipes[PARENT_WRITE_PIPE]) == -1)
		return (error("Pipe failed in the CGI."));
    pid = fork();
	if (pid == -1)
		return (error("Fork failed in the CGI."));
	else if (pid == 0)
	{
		cgi_args[0] = (char *)"/bin/php-cgi";
		cgi_args[1] = (char *)full_path.c_str();
		cgi_args[2] = NULL;
		// Chdir path
		size_t		file_len = 0;
		for (size_t i = full_path.size() - 1 ; i > 0 ; --i)
		{
			if (full_path[i] == '/')
				break ;
			++file_len;
		}
		std::string	cd_path = full_path.substr(0, full_path.size() - file_len);
		if (chdir(cd_path.c_str()) != 0)
			return (error("chdir() failed"));
		dup2(CHILD_READ_FD, STDIN_FILENO);
		dup2(CHILD_WRITE_FD, STDOUT_FILENO);
		close(CHILD_READ_FD);
        close(CHILD_WRITE_FD);
        close(PARENT_READ_FD);
        close(PARENT_WRITE_FD);
		pid = execve(cgi_args[0], cgi_args, _env);
		return (1);
	}
	else
	{
		char	buffer[BUFFER_SIZE];
		ssize_t	read_return = BUFFER_SIZE;

		close(CHILD_READ_FD);
		close(CHILD_WRITE_FD);
		while (true)
		{
			bzero(buffer, read_return);
			read_return = read(PARENT_READ_FD, buffer, BUFFER_SIZE - 1);
			if (read_return == -1)
				return (error("Read failed in the CGI."));
			buffer[read_return] = 0;
			if (read_return == 0)
			{
				char zero[1];
				zero[0] = '\0';
				_body.append(zero, 1);
				break ;
			}
			_body.append(buffer, read_return);
		}
		close(pipes[PARENT_READ_PIPE][0]);
		close(pipes[PARENT_READ_PIPE][1]);
		close(pipes[PARENT_WRITE_PIPE][0]);
		close(pipes[PARENT_WRITE_PIPE][1]);
	}

	const std::string	code = "200";
	const std::string	message = _status_code_map.find(200)->second;
	_header = _request.get_http_version() + " " + code + " " + message + "\r\n";
	size_t	header_in_body = _body.find("\r\n\r\n");
	if (header_in_body != std::string::npos)
		_header += "Content-Length: " + itostring(_body.size() - header_in_body - 4) + "\r\n";
	else
		_header += "Content-Length: " + itostring(_body.size()) + "\r\n\r\n";
	_response = _header + _body;

	return (0);
};
