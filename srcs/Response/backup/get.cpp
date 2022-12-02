#include "Response.hpp"

bool	Response::is_a_directory(const std::string & path)
{
	struct stat	path_stat;

	bzero(&path_stat, sizeof(path_stat));
	stat(path.c_str(), &path_stat);
	return (S_ISDIR(path_stat.st_mode));
};

// get the body of the response which is the html file
int		Response::stored_file(string  path)
{
	std::ifstream	file;
	string			buf;
	double			current_size = 0;
	const double	max_size = _server.get_max_size();

	file.open(path.c_str(), std::ios::in);
	if (file.is_open() == false)
	{
		generate_error_page(404);
		return (1);
	}
	_response_body.clear();
	while (!file.eof())
	{
		getline(file, buf);
		_response_body += buf;
		if (max_size > 0)
		{
			current_size += buf.size();
			if (current_size > max_size)
				break ;
		}
		if (!file.eof())
		{
			_response_body += '\n';
			++current_size;
		}
	}
	file.close();
	return (set_status_code(200));
};

bool	Response::match_extension(void)
{
	string ext;
	std::vector<string> cgi_ext;

	if (_file_path.size() > 3)
	{
		ext = _file_path.substr(_file_path.size() - 4, _file_path.size());
		cgi_ext = _location.cgi_extensions();
		for (size_t i = 0; i < cgi_ext.size(); i++)
		{
			if (cgi_ext[i] == ext)
				return (1);
		}
	}
	return (0);
}

void 	Response::get(void)
{
	if (get_location())
	{
		generate_error_page(404);
		return ;
	}
	if (_location.redirection() == true)
	{
		_status_code = _location.get_redirection_code();
		const std::string	code  = itostring(_status_code);

		_response_header = _request.get_http_version() + " " + code + " " + _status_code_map.find(_status_code)->second + "\r\n";
		_response_header += "Location: " + _location.get_redirection_path() + "\r\n\r\n";
		_response_body = "";
		_full_response = _response_header + _response_body;
		return ;
	}
	if (_location.get_allowed() == false)
	{
		generate_error_page(405);
		return ;
	}
	if (path_construction())
	{
		generate_error_page(404);
		return ;
	}
	if (is_a_directory(_file_path) && _dir == true)
	{
		if (_location.directory_file_set)
		{
			_status_code = 415;
			const std::string	message = _status_code_map.find(_status_code)->second;
			_response_header = _request.get_http_version() + " 415 " + message + "\r\n\r\n";
			_response_body = _location.get_directory_file();
			_full_response = _response_header + _response_body;
		}
		else if (_location.directory_listing() == true)
			list_directories();
		else
			generate_error_page(415);
		return ;
	}
	if (_location.cgi_set == true && match_extension())
	{
		if (!build_cgi_response(_file_path))
			return ;
	}
	else
		stored_file(_file_path);
	build_http_response();
};
