#include "Response.hpp"

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
