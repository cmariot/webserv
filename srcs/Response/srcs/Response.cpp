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

// int		Response::create_response_header(void)
// {
// 	const std::string	code  = itostring(_status_code);

// 	_response_header = _request.http_version + " " + code + " " + _status_code_map.find(_status_code)->second + "\r\n\r\n";
// 	return (0);
// };

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

void	Response::post(void)
{
	size_t i = 0;
	
	struct stat buff;
	string folder = _location.get_upload_path();
	// if (stat(folder.c_str(), &buff) != 0)
	// 	mkdir(folder.c_str(), 0777);
	cout << folder << endl;
	if(mkdir(folder.c_str(), 0777))
		print(INFO, "Upload folder created");


	while (i < _request.content.size())
	{
		string infile(_request.file_name[i]);
		std::ofstream fout;

		infile = _location.get_upload_path() + infile;
		fout.open(infile.c_str(), std::ios::out | std::ios::app);
		if (fout.is_open() == false)
		{
			error("Error : while opening the file ", infile);
			_full_response = "HTTP/1.1 201 OK\r\n\r\n";;
		}
		fout << _request.body_content[i];
		fout.close();
		_full_response = "HTTP/1.1 201 Created\r\n\r\n Created";
		i++;
	}
}

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
	if (_request.method == "DELETE" && _location.delete_allowed())
		return (0);
	if (_request.method == "POST" && _location.post_allowed())
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
		print(INFO, ("Response =\n" + _full_response).c_str());
		send(fd, _full_response.c_str(), _full_response.size(), 0);
		print(INFO, "The response has been sent to the client");
		return ;
	}
	else if (_request.method == "POST")
	{
		if (!test_authorization())
		{
			post();
			build_http_response();
			print(INFO, "Files were succesfully uploaded to the server");
		}
	}
	else if (_request.method == "DELETE")
	{
		// if (!test_authorization())
			//delete();
	}
	else
	{
		set_status_code(501);
		build_http_response();
	}
	print(INFO, ("Response =\n" + _full_response).c_str());
	send(fd, _full_response.c_str(), _full_response.size(), 0);
	print(INFO, "The response has been sent to the client");
};
