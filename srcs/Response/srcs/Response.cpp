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


static bool	method_allowed(const string &method)
{
	if (method == "GET" || method == "POST" || method == "DELETE")
		return (true);
	return (false);
}

bool 		Response::headers_check(void)
{
	cout << _request.
}

bool		Response::check_request(void)
{
	if(get_location() && path_construction())
	{
		generate_error_page(404);
		return (true);
	}
	if(method_allowed(_request.get_method()) == false)
	{
		generate_error_page(405);
		return (true);
	}
	if (hearders_check())
	{
		generate_error_page(400);
		return (true);
	}

	return (false);

}

// main function used to send the response to the client
void	Response::create()
{
	print(INFO, "Creating the server's response");
	
	if (check_request())
		return ;
	else if (_request.get_method() == "GET")
	{
		get();
	}
	else if (_request.get_method()  == "POST" && _request.content.size())
	{
		_request.get_content();
		print(INFO, "POST request about to be processed");
		post();
	}
	else if (_request.get_method()  == "DELETE" )
	{
		delet();
	}
	else
		set_status_code(501);
	build_http_response();
	// print(INFO, ("Response =\n" + _full_response).c_str());
};
