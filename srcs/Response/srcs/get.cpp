#include "Response.hpp"

void	Response::generate_file_response(void)
{
	//_status_code = 415;
	//const std::string	message = _status_code_map.find(_status_code)->second;
	//_response_header = _request.get_http_version() + " 415 " + message + "\r\n\r\n";
	//_response_body = _location.get_directory_file();
	//_full_response = _response_header + _response_body;
	return ;
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

bool	Response::construct_path(void)
{
	return (false);
};

void	Response::generate_redirection(void)
{
	//_status_code = _location.get_redirection_code();
	//const std::string	code  = itostring(_status_code);
	//_response_header = _request.get_http_version() + " " + code + " " + _status_code_map.find(_status_code)->second + "\r\n";
	//_response_header += "Location: " + _location.get_redirection_path() + "\r\n\r\n";
	//_response_body = "";
	//_full_response = _response_header + _response_body;
	return ;
};

bool	Response::redirection(void) const
{
	return (false);
};

void    Response::get_method(void)
{
	if (redirection())
        return (generate_redirection());
	if (construct_path())
		return (generate_error_page(404));
	if (is_forbidden())
         return (generate_error_page(403));
    if (is_a_directory())
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
	return (generate_file_response());
};
