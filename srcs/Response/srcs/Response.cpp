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
	std::string	code;

	code = itostring(_status_code);
	_response_header = _request.http_version + " " + code + " " + _status_code_map.find(_status_code)->second + "\r\n\r\n";
	std::cout << "Response_header = " << _response_header << std::endl;
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
	// size_t i = 0;

	// while (i < _request.content.size())
	// {
	// 	string infile(_request.file_name[i]);
	// 	std::ofstream fout;
	// 	fout.open(infile.c_str(), std::ios::out | std::ios::app);

	// 	cout << _request.body_content[i] << endl;

	// 	if (fout.is_open() == false)
	// 	{
	// 		error("Error : while opening the file ", infile);
	// 		_full_response = "HTTP/1.1 201 OK\r\n\r\n";;
	// 	}
	// 	// cout << "content added \n" << _request.body_content << cout;
	// 	fout << _request.body_content[i];
	// 	fout.close();
	// 	_full_response = "HTTP/1.1 201 Created\r\n\r\n Created";
	// 	i++;
	// }
}

// main function used to send the response to the client
void	Response::create(int fd)
{
	print(INFO, "Creating the server's response");
	if (_request.method == "GET")
	{
		get();
	}
	else if (_request.method == "POST")
	{
		post();
	}
	else if (_request.method == "DELETE")
	{
		//delete();
	}
	else
	{
		set_status_code(501);
	}
	send(fd, _full_response.c_str(), _full_response.size(), 0);
	print(INFO, "The response has been sent to the client");
};
