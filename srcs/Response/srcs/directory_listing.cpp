#include "Response.hpp"
#include <dirent.h>

void	Response::add_dot_link(void)
{
	_response_body += "<a href=\"" + _request.get_uri() + "\">.</a>";
};

void	Response::add_double_dot_link(void)
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
		_response_body += "<a href=\"" + link + "\">..</a>";
	}
};

void	Response::add_other_link(char d_name[256])
{
	std::string		link;

	if (_request.get_uri().size() > 0 && _request.get_uri()[_request.get_uri().size() - 1] != '/')
		link = _request.get_uri() + "/";
	else
		link = _request.get_uri();
	link += d_name;
	_response_body += "<a href=\"" + link + "\">" + d_name + "</a>";
};

void	Response::directory_listing_body(void)
{
	DIR				*d;
	struct dirent	*dir;

	d = opendir(_file_path.c_str());
	if (!d)
		return (generate_error_page(404));
	_response_body =  "<!DOCTYPE html>";
	_response_body += "<html lang=\"en\">";
	_response_body +=	"<head>";
	_response_body +=		"<meta charset=\"utf-8\">";
	_response_body += 		"<title>Webserv</title>";
	_response_body += 		"<style>";
	_response_body +=			"html{";
	_response_body +=				"height:100%;";
	_response_body +=				"width:100%;";
	_response_body += 			"}";
	_response_body += 			"body{";
	_response_body +=				"height:100%;";
	_response_body +=				"width:100%;";
	_response_body +=				"display:flex;";
	_response_body +=				"flex-direction:column;";
	_response_body +=				"justify-content:center;";
	_response_body +=				"align-content:center;";
	_response_body +=				"text-align:center;";
	_response_body += 			"}";
	_response_body += 		"</style>";
	_response_body += 	"</head>";
	_response_body += 	"<body>";
	_response_body +=		"<h1>Index of " + _file_path + "</h1>";
	while ((dir = readdir(d)) != NULL)
	{
		if (memcmp(dir->d_name, ".", strlen(dir->d_name)) == 0)
			add_dot_link();
		else if (memcmp(dir->d_name, "..", strlen(dir->d_name)) == 0)
			add_double_dot_link();
		else
			add_other_link(dir->d_name);
	}
	_response_body += 	"</body>";
	_response_body += "</html>";
	closedir(d);
	return ;
}

void	Response::directory_listing_header(void)
{
	const std::string	code = "200";
	const std::string	message = _status_code_map.find(200)->second;

	_status_code = 200;
	_response_header = _request.get_http_version() + " " + code + " " + message + "\r\n\r\n";
	return ;
}

int	Response::list_directories(void)
{
	directory_listing_header();
	directory_listing_body();
	_full_response = _response_header + _response_body;
	return (0);
};
