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

	_response_header = _request.http_version + " " + code + " " + _status_code_map.find(_status_code)->second + "\r\n\r\n";

	if (_status_code >= 300 && _server.get_error_pages().find(_status_code) != _server.get_error_pages().end())
		stored_file(_server.get_error_pages().find(_status_code)->second.get_path());
	else if (_status_code >= 300)
	{	generate_error_page(_status_code);
		return;
	}

	_full_response = _response_header + _response_body;
};


// Check if methods allowed in the location
int	Response::test_authorization(void)
{
	if (get_location())
	{
		generate_error_page(404);
		return (1) ;
	}
	if (_request.method == "GET" && _location.get_allowed())
		return (0);
	else if (_request.method == "DELETE" && _location.delete_allowed())
		return (0);
	else if (_request.method == "POST" && _location.post_allowed())
		return (0);
	set_status_code(403);
	build_http_response();
	return (1);
}

// main function used to send the response to the client
void	Response::create(int fd)
{
	print(INFO, "Creating the server's response");
	if (_request.method == "GET")
	{
		get();
		// print(INFO, ("Response =\n" + _full_response).c_str());
		send(fd, _full_response.c_str(), _full_response.size(), 0);
		print(INFO, "The response has been sent to the client");
		return ;
	}
	else if (_request.method == "POST" && !test_authorization() && _request.content.size())
	{
		post();
	}
	else if (_request.method == "DELETE" && !test_authorization() && _request.file_name())
	{
		cout << _request.uri << endl;
		// delete();
	}
	else
		set_status_code(501);
	build_http_response();
	// print(INFO, ("Response =\n" + _full_response).c_str());
	send(fd, _full_response.c_str(), _full_response.size(), 0);
	print(INFO, "The response has been sent to the client");
};
