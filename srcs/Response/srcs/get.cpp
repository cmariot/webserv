#include "Response.hpp"

static bool	get_file(const std::string & path, std::string & file_content)
{
	std::ifstream	file;
	char			buffer[BUFFER_SIZE];
	int				read_return = BUFFER_SIZE;

	file.open(path.c_str(), std::ifstream::in | std::ifstream::binary);
	if (file.is_open() == false)
		return (false);
	file_content.clear();
	while (true)
	{
		bzero(buffer, read_return);
		file.read(buffer, sizeof(char) * BUFFER_SIZE);
		read_return = file.gcount();
		if (read_return == 0 || read_return == -1)
			break ;
		file_content.append(buffer, read_return);
	}
	file.close();
	if (read_return == -1)
		return (false);
	return (true);
};

void	Response::generate_file_response(void)
{
	if (get_file(_path, _body))
	{
		const int			& status_code	= 200;
		const std::string	& code			= itostring(status_code);

		_header  = _request.get_http_version() + " " + code + " " + _status_code_map.find(status_code)->second + "\r\n";
		_header += "Content-Length: " + itostring(_body.size()) + "\r\n\r\n";
		_response = _header + _body;
	}
	else
		return (generate_error_page(502));
};

bool	Response::use_cgi(void) const
{
	if (_location.cgi_set == true)
	{
		const std::vector<string> & extensions = _location.cgi_extensions();

		for (size_t i = 0 ; i < extensions.size() ; ++i)
			if (_path.size() > extensions[i].size())
				if (_path.find(extensions[i]) == _path.size() - extensions[i].size())
					return (true);
	}
	return (false);
};

bool	Response::is_a_directory(void) const
{
	return (is_a_dir(_path));
};

bool	Response::is_forbidden(void) const
{
	struct stat	file_stat;

	if (stat(_path.c_str(), &file_stat) == 0)
		if (file_stat.st_mode & S_IRUSR)
			return (false);
	return (true);
};

bool	Response::file_not_found(void)
{
	_path = _request.get_uri();
	std::cout << "PATH 1 : " <<  _path << std::endl;
	_path.replace(0, _location.get_uri().size(), _location.root());
	std::cout << "PATH 2 : " << _path << std::endl;
	if (is_a_file(_path))
		return (false);	 /* (￣o￣) zzZZzzZZ */
	for (size_t i = 0 ; i < _location.index().size() ; ++i)
	{
		std::string test_path = _path + _location.index()[i];
		if (is_a_file(test_path))
		{
			_path = test_path;
			return (false);
		}
	}
	if (is_a_dir(_path))
		return (false);
	return (true);
};

void	Response::generate_redirection(void)
{
	const int			& status_code	= _location.get_redirection_code();
	const std::string	& code			= itostring(status_code);

	_response  = _request.get_http_version() + " " + code + " " + _status_code_map.find(status_code)->second + "\r\n";
	_response += "Content-Length: 0\r\n";
	_response += "Location: " + _location.get_redirection_path() + "\r\n\r\n";
	return ;
};

bool	Response::redirection(void) const
{
	if (_location.redirection())
		return (true);
	return (false);
};

void    Response::get_method(void)
{
	if (redirection())
        return (generate_redirection());
	if (file_not_found())
		return (generate_error_page(404));
	if (is_forbidden())
         return (generate_error_page(403));
	else if (is_a_directory())
	{
		if (directory_file_set())
			return (generate_directory_file());
		else if (directory_listing_set())
			return (generate_directory_list());
		else
			return (generate_error_page(415));
	}
	if (use_cgi())
	{
		if (generate_cgi_response())
			return (generate_error_page(400));
		return ;
	}
	return (generate_file_response());
};
