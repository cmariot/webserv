#include "Response.hpp"

// Generate default webserv error responses

void	Response::generate_error_page(const int & error_code)
{
	_status_code = error_code;

	const std::string	code  = itostring(_status_code);
	const std::string	message = _status_code_map.find(_status_code)->second;
	string 		content_length;
	_response_header = _request.get_http_version() + " " + code + " " + message;

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
	_response_body +=		"<h1>Webserv : Error " + code + "</h1>";
	_response_body +=		"<h2>" + message + "</h2>";
	_response_body += 	"</body>";
	_response_body += "</html>";

	content_length = "\r\nContent-length:" + itostring(_response_body.size()) + "\r\n\r\n";
	cout << content_length << endl;
	_full_response = _response_header + content_length + _response_body;

	return ;
};
