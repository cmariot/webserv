#include "Response.hpp"

static bool	is_a_dir(const std::string & path)
{
	struct stat	path_stat;

	bzero(&path_stat, sizeof(path_stat));
	stat(path.c_str(), &path_stat);
	return (S_ISDIR(path_stat.st_mode));
};

static	bool	is_a_file(const std::string & path)
{
	struct stat path_stat;

	bzero(&path_stat, sizeof(path_stat));
	if (stat(path.c_str(), &path_stat) != 0)
		return (false);
	return (S_ISREG(path_stat.st_mode));
};

static bool	get_file(const std::string & path, std::string & file_content)
{
	std::ifstream	file;
	string			buf;

	file.open(path.c_str(), std::ios::in);
	if (file.is_open() == false)
		return (false);
	while (!file.eof())
	{
		getline(file, buf);
		file_content += buf;
	}
	file.close();
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
		return (generate_error_page(404));
};

void	Response::generate_cgi_response(void)
{
	//_status_code = 415;
	//const std::string	message = _status_code_map.find(_status_code)->second;
	//_response_header = _request.get_http_version() + " 415 " + message + "\r\n\r\n";
	//_response_body = _location.get_directory_file();
	//_full_response = _response_header + _response_body;
	return ;
};

bool	Response::use_cgi(void) const
{
	return (false);
};

void	Response::generate_directory_list(void)
{
	//_status_code = 415;
	//const std::string	message = _status_code_map.find(_status_code)->second;
	//_response_header = _request.get_http_version() + " 415 " + message + "\r\n\r\n";
	//_response_body = _location.get_directory_file();
	//_full_response = _response_header + _response_body;
	return ;
};

bool	Response::directory_listing_set(void) const
{
	return (false);
};

void	Response::generate_directory_file(void)
{
	//_status_code = 415;
	//const std::string	message = _status_code_map.find(_status_code)->second;
	//_response_header = _request.get_http_version() + " 415 " + message + "\r\n\r\n";
	//_response_body = _location.get_directory_file();
	//_full_response = _response_header + _response_body;
	return ;
};

bool	Response::directory_file_set(void) const
{
	return (false);
};

bool	Response::is_a_directory(void) const
{
	return (false);
};

bool	Response::is_forbidden(void) const
{
	return (false);
};

bool	Response::file_not_found(void)
{
	_path = _request.get_uri();
	_path.replace(0, _location.get_uri().size(), _location.root());
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
	else if (is_forbidden())
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
		return (generate_cgi_response());
	else
		return (generate_file_response());
};
