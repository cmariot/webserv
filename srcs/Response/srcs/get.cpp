#include "Response.hpp"

void    Response::get(void)
{
	if (_location.redirection() == true)
	{
        return (create_redirection());

		//_status_code = _location.get_redirection_code();
		//const std::string	code  = itostring(_status_code);
		//_response_header = _request.get_http_version() + " " + code + " " + _status_code_map.find(_status_code)->second + "\r\n";
		//_response_header += "Location: " + _location.get_redirection_path() + "\r\n\r\n";
		//_response_body = "";
		//_full_response = _response_header + _response_body;
	}
	if (path_construction())
		return (generate_error_page(404));
	// if (forbidden())
        // return (generate_error_page(403));
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
    return ;
};