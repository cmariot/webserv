#include "Webserver.hpp"

// check the request and return the corresponding header response
string	Webserver::server_http_header_response(string method, string path)
{
	// to complete with other types of header responses (404, 500, 501, 505) etc
	string response;
	// Il faut checkew si les fichier existe bien
	// check if the request is a GET request -> add checking existance du file avec stored_file

	if (method == "GET")
	{
		if (path == "/" || path == "/index.html" || path == "/index.html/" )
		{
			response = "HTTP/1.1 200 OK\r\n\r\n";
			response += stored_file("./html/index.html");
		}
		else
		{
			response = "HTTP/1.1 404 Not Found\r\nContent-Length: 165\r\nContent-Type: text/html\r\n\n 404 bish get";
		}
	}
	else
		response = "HTTP/1.1 404 Not Found\r\nContent-Length: 165\r\nContent-Type: text/html\r\n\n 404 bish";
	// add other reauest

	return response;
}
