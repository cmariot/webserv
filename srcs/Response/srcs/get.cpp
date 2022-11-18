#include "Response.hpp"

bool	Response::is_a_directory(const std::string & path)
{
	struct stat	path_stat;

	bzero(&path_stat, sizeof(path_stat));
	stat(path.c_str(), &path_stat);
	return (S_ISDIR(path_stat.st_mode));
};

// get the body of the response which is the html file
int		Response::stored_file(string & path)
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

void 	Response::get(void)
{
	if (get_location()) // No location block found
	{
		generate_error_page(404);
		return ;
	}
	if (_location.redirection() == true)
	{
		_status_code = _location.get_redirection_code();
		// Check du redirection code ? (code < 200 || code > 400 = error ?)
		const std::string	code  = itostring(_status_code);

		_full_response = _request.http_version + " " + code + " " + _status_code_map.find(_status_code)->second + "\r\n";
		_full_response += "Location: " + _location.get_redirection_path() + "\r\n\r\n";
		return ;
	}
	if (_location.get_allowed() == false)
	{
		generate_error_page(405);
		// check error_page redirection
		return ;
	}
	if (path_construction())
	{
		generate_error_page(404);
		return ;
	}
	if (is_a_directory(_file_path))
	{
		if (_location.directory_listing() == true)
		{
			list_directories();
			return ;
		}
		else
		{
			generate_error_page(415);
			return ;
		}
	}
	if (_location.cgi_set == true)
	{
		std::cout << "HOHO" <<std::endl;
		if (!build_cgi_response())
			return ;
	}
	stored_file(_file_path);
	// CGI ?
	if (_server.get_max_size() > 0)
	{
		if (_response_body.size() > _server.get_max_size())
		{
			generate_error_page(413);
			return ;
		}
	}
	// Error page redirection ?
	build_http_response();
};
