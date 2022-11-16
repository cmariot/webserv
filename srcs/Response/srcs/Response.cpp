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

	_response_header = _request.http_version + " " + code + " " + _status_code_map.find(_status_code)->second + "\r\n\r\n";
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

void	Response::post(void)
{
	// std::cout << _request.request << std::endl;

	string infile(_request.file_name);
	std::ofstream fout;
	fout.open(infile.c_str(), std::ios::out | std::ios::app);
	if (fout.is_open() == false)
	{
		error("Error : while opening the file ", infile);
		_full_response = "HTTP/1.1 201 OK\r\n\r\n";;
	}
	// cout << "content added \n" << _request.body_content << cout;
	fout << _request.body_content;
	fout.close();
	_full_response = "HTTP/1.1 201 Created\r\n\r\n Created";;
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
		post();
		build_http_response();
	}
	else if (_request.method == "DELETE")
	{
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
