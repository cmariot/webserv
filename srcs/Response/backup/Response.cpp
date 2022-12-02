#include "Response.hpp"

// Basic setter for status code
int	Response::set_status_code(const int & status_code)
{
	_status_code = status_code;
	return (status_code);
};

// inline is to make a quicker
// This function is to verify if the file exists or not (quicker execution than fopen)
// stat return -1 if the file does not exist 0 if it does
bool Response::check_file_existance(string &file)
{
	struct stat	buffer;

	return (stat(file.c_str(), &buffer) == 0);
};


void	Response::build_http_response(void)
{
	const std::string	code  = itostring(_status_code);

	_response_header = _request.get_http_version() + " " + code + " " + _status_code_map.find(_status_code)->second + "\r\nContent-length:"+ itostring(_response_body.size()) +"\r\n\r\n";

	if (_status_code >= 300 && _server.get_error_pages().find(_status_code) != _server.get_error_pages().end())
		stored_file(_server.get_error_pages().find(_status_code)->second.get_path());
	else if (_status_code >= 300)
	{	generate_error_page(_status_code);
		return;
	}

	_full_response = _response_header + _response_body;
};


<<<<<<< HEAD:srcs/Response/backup/Response.cpp
// Check if methods allowed in the location
int	Response::test_authorization(void)
{
	if (get_location())
	{
		generate_error_page(404);
		return (1);
	}
	if (_request.get_method() == "GET" && _location.get_allowed())
		return (0);
	else if (_request.get_method() == "DELETE" && _location.delete_allowed())
		return (0);
	else if (_request.get_method() == "POST" && _location.post_allowed())
		return (0);
	set_status_code(403);
	build_http_response();
	return (1);
}

=======
>>>>>>> d43fe919a4fa1de27050bbf9b7c808933b13712d:srcs/Response/srcs/Response.cpp
// main function used to send the response to the client
void	Response::create()
{
	print(INFO, "Creating the server's response");
	
	if (check_request())
		return ;
	if (_request.get_method() == "GET")
	{
		get();
	}
<<<<<<< HEAD:srcs/Response/backup/Response.cpp
	else if (_request.get_method()  == "POST" && !test_authorization())
=======
	else if (_request.get_method()  == "POST")
>>>>>>> d43fe919a4fa1de27050bbf9b7c808933b13712d:srcs/Response/srcs/Response.cpp
	{
		_request.get_content();
		print(INFO, "POST request about to be processed");
		post();
	}
	else if (_request.get_method()  == "DELETE")
	{
		delet();
	}

	build_http_response();
	// print(INFO, ("Response =\n" + _full_response).c_str());
};
