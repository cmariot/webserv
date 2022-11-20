#include "Response.hpp"

#include <dirent.h>

int	Response::list_directories(void)
{
	DIR				*d;
	struct dirent	*dir;
	std::string		tmp;

	d = opendir(_file_path.c_str());
	if (!d)
	{
		generate_error_page(404);
		return (1);
	}

	_status_code = 200;
	const std::string	code  = itostring(_status_code);
	const std::string	message = _status_code_map.find(_status_code)->second;
	_response_header = _request.http_version + " " + code + " " + message + "\r\n\r\n";

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

	size_t	pos = _response_body.size();

	while ((dir = readdir(d)) != NULL)
	{
		tmp = _request.uri + "/";
		tmp += dir->d_name;
		std::cout << tmp << std::endl;
		_response_body.insert(pos, ("<a href=\"" + tmp + "\">" + dir->d_name + "</a>"));
	}
	closedir(d);

	_response_body += 	"</body>";
	_response_body += "</html>";

	_full_response = _response_header + _response_body;

	return (0);
};
