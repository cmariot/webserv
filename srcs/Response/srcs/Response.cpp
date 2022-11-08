#include "Response.hpp"


// basic h
void 	Response::init_status_code_map(void)
{
	_status_code_map.insert(pair<int, string>(200, "OK"));
	_status_code_map.insert(pair<int, string>(201, "Created"));
	_status_code_map.insert(pair<int, string>(202, "Accepted"));
	_status_code_map.insert(pair<int, string>(203, "Non-Authoritative Information"));
	_status_code_map.insert(pair<int, string>(204, "No Content"));
	_status_code_map.insert(pair<int, string>(205, "Reset Content"));
	_status_code_map.insert(pair<int, string>(206, "Partial Content"));
	_status_code_map.insert(pair<int, string>(300, "Multiple Choices"));
	_status_code_map.insert(pair<int, string>(301, "Moved Permanently"));
	_status_code_map.insert(pair<int, string>(302, "Found"));
	_status_code_map.insert(pair<int, string>(303, "See Other"));
	_status_code_map.insert(pair<int, string>(304, "Not Modified"));
	_status_code_map.insert(pair<int, string>(305, "Use Proxy"));
	_status_code_map.insert(pair<int, string>(307, "Temporary Redirect"));
	_status_code_map.insert(pair<int, string>(400, "Bad Request"));
	_status_code_map.insert(pair<int, string>(401, "Unauthorized"));
	_status_code_map.insert(pair<int, string>(402, "Payment Required"));
	_status_code_map.insert(pair<int, string>(403, "Forbidden"));
	_status_code_map.insert(pair<int, string>(404, "Not Found"));
	_status_code_map.insert(pair<int, string>(405, "Method Not Allowed"));
	_status_code_map.insert(pair<int, string>(406, "Not Acceptable"));
	_status_code_map.insert(pair<int, string>(407, "Proxy Authentication Required"));
	_status_code_map.insert(pair<int, string>(408, "Request Time-out"));
	_status_code_map.insert(pair<int, string>(409, "Conflict"));
	_status_code_map.insert(pair<int, string>(410, "Gone"));
	_status_code_map.insert(pair<int, string>(411, "Length Required"));
	_status_code_map.insert(pair<int, string>(412, "Precondition Failed"));
	_status_code_map.insert(pair<int, string>(413, "Request Entity Too Large"));
	_status_code_map.insert(pair<int, string>(414, "Request-URI Too Large"));
	_status_code_map.insert(pair<int, string>(415, "Unsupported Media Type"));
	_status_code_map.insert(pair<int, string>(416, "Requested range not satisfiable"));
	_status_code_map.insert(pair<int, string>(417, "Expectation Failed"));
	_status_code_map.insert(pair<int, string>(500, "Internal Server Error"));
	_status_code_map.insert(pair<int, string>(501, "Not Implemented"));
	_status_code_map.insert(pair<int, string>(502, "Bad Gateway"));
	_status_code_map.insert(pair<int, string>(503, "Service Unavailable"));
	_status_code_map.insert(pair<int, string>(504, "Gateway Time-out"));
	_status_code_map.insert(pair<int, string>(505, "HTTP Version not supported"));
}

// inline is to make a quicker 
// This function is to verify if the file exists or not (quicker execution than fopen)
inline bool Response::check_file_existance(string &file) {
  struct stat buffer; 
  return (stat (file.c_str(), &buffer) == 0); 
}

// get the body of the response which is the html file
int		Response::stored_file(string path)
{
	string infile(path);										// The file we open
	std::ifstream fin;											//infile stream -> fichier de flux d'entree
	fin.open(infile.c_str(), std::ios::in);
	if (!fin)
	{
		std::cerr << "Error : while opening the file " << infile << endl;
		return(1);
	}

	string tmp = "";
   	string input = "";
	while (!fin.eof())
	{
		getline(fin, tmp);
		input += tmp;
		if (!fin.eof())
			input += '\n';
	}
	fin.close();													// Closing the infile
	return 0;
};

// depending of request implementation
int 	Response::get_response(
{

	if (check_file_existance(request::get_path()) == false)
	{
		// 404
	}
	else
	{
		// 200
	}
	{
		stored_file(path);
		_status_code = 200;
	}
	else
	{
		_status_code = 404;
	}
	return 0;
}
