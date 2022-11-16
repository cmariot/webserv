#include "Response.hpp"

// get the body of the response which is the html file
int		Response::stored_file(string & path)
{
	std::ifstream	file;
	string			buf;

	file.open(path.c_str(), std::ios::in);
	if (file.is_open() == false)
		return (set_status_code(404));
	_response_body.clear();
	while (!file.eof())
	{
		getline(file, buf);
		_response_body += buf;
		if (!file.eof())
			_response_body += '\n';
	}
	file.close();
	return (set_status_code(200));
};

void	Response::generate_error_page(const int & error_page)
{
	_status_code = error_page;

	const std::string	code  = itostring(_status_code);
	const std::string	message = _status_code_map.find(_status_code)->second;

	_response_header = _request.http_version + " " + code + " " + message + "\r\n\r\n";

	_response_body =  "<!DOCTYPE html>";
	_response_body += "<html lang=\"en\">";
	_response_body += "<head>";
	_response_body += "<meta charset=\"utf-8\">";
	_response_body += "<title>Webserv</title>";
	_response_body += "<style>";
	_response_body += "html{";
	_response_body += "height: 100%;";
	_response_body += "width: 100%;";
	_response_body += "}";
	_response_body += "body{";
	_response_body += "height: 100%;";
	_response_body += "width: 100%;";
	_response_body += "display: flex;";
	_response_body += "flex-direction: column;";
	_response_body += "justify-content: center;";
	_response_body += "align-content: center;";
	_response_body += " text-align: center;";
	_response_body += "}";
	_response_body += "</style>";
	_response_body += "</head>";
	_response_body += "<body>";
	_response_body += "<h1>Webserv : Error " + code + "</h1>";
	_response_body += "<h2>" + message + "</h2>";
	_response_body += "</body>";
	_response_body += "</html>";

	_full_response = _response_header + _response_body;
}
								

void 	Response::get(void)
{
	if (get_location())
	{
		generate_error_page(404);
		return ;
	}
	if (_location.get_allowed() == false)
	{
		generate_error_page(405);
		return ;
	}
	if (_location.redirection() == true)
	{
		_status_code = _location.get_redirection_code();
		const std::string	code  = itostring(_status_code);

		_response_header = _request.http_version + " " + code + " " + _status_code_map.find(_status_code)->second + "\r\n";
		_response_header += "Location: " + _location.get_redirection_path() + "\r\n\r\n";
		_full_response = _response_header;
		return ;
	}
	path_construction();
	if (_location.directory_listing() == true)
	{
		//if (is_a_directory(_file_path))
		{

		}
	}
	// CGI ?
	stored_file(_file_path);
	// Error ? -> error page ?
	if (_server.get_max_size() > 0)
	{
		// Max body size ?
	}
	build_http_response();
};
