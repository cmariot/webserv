#include "Webserver.hpp"
// get the body of the response which is the html file
string	 Webserver::stored_file(string path)
{
	string infile(path);										// The file we open
	std::ifstream fin;											//infile stream -> fichier de flux d'entree
	fin.open(infile.c_str(), std::ios::in);
	if (!fin)
	{
		std::cerr << "Error : while opening the file " << infile << endl;
		exit(1);
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
	return input;
}


string	 Webserver::create_http_response(string method, string path)
{
	string response;
	response = server_http_header_response(method, path);
	return response;
}

void parse_request(std::vector<std::string> & data, char *request)
{
    std::string tmp(request);
    int pos = 0;
    while(!tmp.empty())
    {
        pos = tmp.find(' ');
        if (pos != -1)
        {
            data.push_back(tmp.substr(0,pos));
            tmp.erase(0, pos + 1);
        }
        else
        {
            data.push_back(tmp);
            tmp.clear();
        }
    }
}

int Webserver::server_response(int fd, char *request)
{
    std::vector<std::string>    data;
    string                      response;
    string                      method;
    string                      path;


    parse_request(data, request);
    method = data[0];
    for (size_t i = 0 ; i < data.size() ; ++i)
    {
        if (data[i] == method)
        {
            path = data[i + 1];
            break;
        }
    }

    response = create_http_response(method, path);
    send(fd, response.c_str(), response.size(), 0);
    return (0);
}
