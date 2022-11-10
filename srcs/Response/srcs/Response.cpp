#include "Response.hpp"

// Basic setter for status code
void	Response::set_status_code(int status_code)
{
	_status_code = status_code;
};

// inline is to make a quicker
// This function is to verify if the file exists or not (quicker execution than fopen)
inline bool Response::check_file_existance(string &file)
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
	if (_request.uri == "/" || _request.uri == "/index.html" ||
		_request.uri== "/index.html/" )
	{
		stored_file("./html/index.html");
		_status_code = 200;
		_response_header = "HTTP/1.1 200 OK\r\n\r\n";
	}
	else if (check_file_existance(_request.uri))
	{
		if (stored_file(_request.uri))
		{
			_status_code = 500;
		}
		_status_code = 200;
		_response_header = "HTTP/1.1 200 OK\r\n\r\n";
	}
	else
	{
		_status_code = 404;
		_full_response = "HTTP/1.1 404 Not Found\r\nContent-Length: 165\r\nContent-Type: text/html\r\n\n 404 BOUM";
	}
	build_http_response();
};

// main function used to send the response to the client
void	Response::create(int fd)
{
	print(INFO, "Creating the server's response");
	// Trouver le bloc Location (dans _server) correspondant a _request.uri
	// Construire le path a partir de pwd + uri + index
	if (_request.method == "GET")
	{
		get();
	}
	else if (_request.method == "POST")
	{
		//post();
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
