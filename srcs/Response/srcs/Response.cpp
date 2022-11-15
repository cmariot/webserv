#include "Response.hpp"

// Basic setter for status code
void	Response::set_status_code(int status_code)
{
	_status_code = status_code;
};

// inline is to make a quicker
// This function is to verify if the file exists or not (quicker execution than fopen)
bool Response::check_file_existance(string &file)
{
	struct stat	buffer;

	return (stat(file.c_str(), &buffer) == 0);
};

void	Response::build_http_response(void)
{
	if (_status_code == 200)
	{
		_full_response = _response_header + _response_body;
	}
};

// get the body of the response which is the html file
int		Response::stored_file(string path)
{
	string infile(path);										// The file we open
	std::ifstream fin;											//infile stream -> fichier de flux d'entree
	fin.open(infile.c_str(), std::ios::in);
	if (fin.is_open() == false)
		return (error("Error : while opening the file ", infile));
	string tmp = "";
	_response_body = "";
	while (!fin.eof())
	{
		getline(fin, tmp);
		_response_body += tmp;
		if (!fin.eof())
			_response_body += '\n';
	}
	fin.close();													// Closing the infile
	return 0;
};

void 	Response::get(void)
{
	stored_file(_file_path);
	_status_code = 200;
	_response_header = "HTTP/1.1 200 OK\r\n\r\n";
	build_http_response();
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
		if (get_location() == 0)
		{
			path_construction();
			get();
		}
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
