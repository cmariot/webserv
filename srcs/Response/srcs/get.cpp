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
	char			buffer[BUFFER_SIZE];
	int				read_return;

	file.open(path.c_str(), std::ifstream::in | std::ifstream::binary);
	if (file.is_open() == false)
		return (false);
	file_content.clear();
	while (true)
	{
		bzero(buffer, BUFFER_SIZE);
		file.read(buffer, sizeof(char) * BUFFER_SIZE);
		read_return = (int)file.gcount();	
		if (read_return == 0)
			break ;
		file_content.append(buffer, read_return);
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

const std::string Response::add_dot_link(void)
{
	return ("<a href=\"" + _request.get_uri() + "\">.</a>");
};

const std::string Response::add_double_dot_link(void)
{
	std::string		link;

	if (_request.get_uri().size() > 0)
	{
		size_t pos = _request.get_uri().size() - 1;
		if (_request.get_uri()[pos] == '/')
			--pos;
		while (pos)
		{
			if (_request.get_uri()[pos] == '/')
				break ;
			--pos;
		}
		link = _request.get_uri().substr(0, pos) + "/";
		return ("<a href=\"" + link + "\">..</a>");
	}
	return ("");
};

const std::string Response::add_other_link(char d_name[256])
{
	std::string		link;

	if (_request.get_uri().size() > 0 && _request.get_uri()[_request.get_uri().size() - 1] != '/')
		link = _request.get_uri() + "/";
	else
		link = _request.get_uri();
	link += d_name;
	std::string final_link = "<a href=\"" + link + "\">" + d_name + "</a>";
	return (final_link);
};

int		Response::directory_listing_body(void)
{
	DIR				*d;
	struct dirent	*dir;

	d = opendir(_path.c_str());
	if (!d)
		return (1);
	_body =  "<!DOCTYPE html>";
	_body += "<html lang=\"en\">";
	_body +=	"<head>";
	_body +=		"<meta charset=\"utf-8\">";
	_body += 		"<title>Webserv</title>";
	_body += 		"<style>";
	_body +=			"html{";
	_body +=				"height:100%;";
	_body +=				"width:100%;";
	_body += 			"}";
	_body += 			"body{";
	_body +=				"height:100%;";
	_body +=				"width:100%;";
	_body +=				"display:flex;";
	_body +=				"flex-direction:column;";
	_body +=				"justify-content:center;";
	_body +=				"align-content:center;";
	_body +=				"text-align:center;";
	_body += 			"}";
	_body += 		"</style>";
	_body += 	"</head>";
	_body += 	"<body>";
	_body +=		"<h1>Index of " + _path + "</h1>";

	std::string					first_link;
	std::string					second_link;
	std::vector<std::string>	other_link;

	while ((dir = readdir(d)) != NULL)
	{
		if (memcmp(dir->d_name, ".", strlen(dir->d_name)) == 0)
			second_link = add_dot_link();
		else if (memcmp(dir->d_name, "..", strlen(dir->d_name)) == 0)
			first_link = add_double_dot_link();
		else
			other_link.push_back(add_other_link(dir->d_name));
	}
	if (first_link.empty() == false)
		_body += first_link;
	if (second_link.empty() == false)
		_body += second_link;
	for (size_t i = 0 ; i < other_link.size() ; ++i)
		_body += other_link[i];
	_body += 	"</body>";
	_body += "</html>";
	closedir(d);
	return (0);
};

void	Response::generate_directory_list(void)
{
	const int			& code		= 200;
	const std::string	& message	= _status_code_map.find(code)->second;

	_header = _request.get_http_version() + " 200 " + message + "\r\n";
	if (directory_listing_body())
		return (generate_error_page(415));
	_header += "Content-Length: " + itostring(_body.size()) + "\r\n\r\n";
	_response = _header + _body;
	return ;
};

bool	Response::directory_listing_set(void) const
{
	return (_location.directory_listing_set);
};

void	Response::generate_directory_file(void)
{
	const int			& code		= 200;
	const std::string	& message	= _status_code_map.find(code)->second;

	_header = _request.get_http_version() + " 200 " + message + "\r\n";
	_body = _location.get_directory_file();
	_header += "Content-Length: " + itostring(_body.size()) + "\r\n\r\n";
	_response = _header + _body;
	return ;
};

bool	Response::directory_file_set(void) const
{
	return (_location.directory_file_set);
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
