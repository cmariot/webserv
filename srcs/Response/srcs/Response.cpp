#include "Response.hpp"

// Basic setter for status code
int	Response::set_status_code(const int & status_code)
{
	_status_code = status_code;
	return (status_code);
};

// inline is to make a quicker
// This function is to verify if the file exists or not (quicker execution than fopen)
bool Response::check_file_existance(string &file)
{
	struct stat	buffer;

	return (stat(file.c_str(), &buffer) == 0);
};

int		Response::create_response_header(void)
{
	const std::string	code  = itostring(_status_code);

	_response_header = _request.get_http_version() + " " + code + " " + _status_code_map.find(_status_code)->second + "\r\n";
	_response_header += "Content-Length: " + itostring(_response_body.size()) + "\r\n\r\n";
	return (0);
};

void	Response::build_http_response(void)
{
	create_response_header();
	//if (_status_code == 200)
	//{
	_full_response = _response_header + _response_body;
	//}
};

// main function used to send the response to the client
void	Response::create(void)
{
	// basic test ici
	if (_request.get_method() == "GET")
		get();
	else if (_request.get_method() == "POST")
	{
		post();
		build_http_response();
	}
	else if (_request.get_method() == "DELETE")
	{
		//delete();
	}
	else
	{
		set_status_code(501);
		build_http_response();
	}
};
