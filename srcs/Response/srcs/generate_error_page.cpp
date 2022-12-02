#include "Response.hpp"

// Generate default webserv error responses

void	Response::generate_error_page(const int & error_code)
{
	_status_code = error_code;

	const std::string	code  = itostring(_status_code);
	const std::string	message = _status_code_map.find(_status_code)->second;

	_header  = _request.get_http_version() + " " + code + " " + message + "\r\n";

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
	_body +=		"<h1>Webserv : Error " + code + "</h1>";
	_body +=		"<h2>" + message + "</h2>";
	_body += 	"</body>";
	_body += "</html>";

	_header += "Content-length:" + itostring(_body.size()) + "\r\n\r\n";

	_response = _header + _body;

	return ;
};
