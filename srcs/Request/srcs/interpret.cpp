#include "Request.hpp"

// La request line est la 1ere ligne de la requete,
// Request-Line = Method SP Request-URI SP HTTP-Version CRLF
int	Request::get_request_line(std::string & request_line)
{
	size_t			i = 0;

	request_line.clear();
	while (i < request.size())
	{
		request_line += request[i];
		if (request[i] == '\n')
			break ;
		++i;
	}
	if (request_line.empty())
		return (error("Invalid request line."));
	return (0);
}

// 1ere partie de la Request-line : Methode
int	Request::get_method(std::string & request_line, size_t & i)
{
	_method.clear();
	while (i < request_line.size())
	{
		if (request_line[i] == ' ')
			break ;
		_method += request_line[i++];
	}
	while (request_line[i] == ' ')
		i++;
	if (_method.empty() || (_method != "GET" && _method != "POST" && _method != "DELETE"))
		return (error("Invalid method in the request line."));
	return (0);
}

// 2nde partie de la Request-line : l'URI
int	Request::get_request_uri(std::string & request_line, size_t & i)
{
	_request_uri.clear();
	while (i < request_line.size())
	{
		if (request_line[i] == ' ')
			break ;
		_request_uri += request_line[i++];
	}
	while (request_line[i] == ' ')
		i++;
	if (_request_uri.empty())
		return (error("Invalid request_uri in the request line."));
	return (0);
}

// 3eme partie de la Request-line : Version HTTP
int	Request::get_http_version(std::string & request_line, size_t & i)
{
	_http_version.clear();
	while (i < request_line.size() && request_line[i] != '\n')
		_http_version += request_line[i++];
	if (_request_uri.empty())
		return (error("Invalid _http_version in the request line."));
	return (0);
}

// 2eme ligne de la requete,
// nous donne des informations sur le serveur auquel on va envoyer la reponse 
int	Request::get_host(void)
{
	size_t	pos = 0;

	_host.clear();
	pos = request.find("Host:");
	if (pos == std::string::npos)
		return (error("No Host in the request"));
	pos += strlen("Host:");
	while (pos < request.size() && request[pos] == ' ')
		++pos;
	while (pos < request.size())
	{
		if (request[pos] == '\n' || request[pos] == ' ')
			break ;
		_host += request[pos++];
	}
	if (_host.empty())
		return (error("No Host in the request"));
	return (0);
};

// Un peu de parsing sur la requete pour obtenir les informations qui nous interessent
int	Request::interpret(void)
{
	std::string		request_line;
	size_t			i = 0;

	//std::cout << request << std::endl;
	if (get_request_line(request_line))
		return (1);
	else if (get_method(request_line, i))
		return (1);
	else if (get_request_uri(request_line, i))
		return (1);
	else if (get_http_version(request_line, i))
		return (1);
	else if (get_host())
		return (1);

	std::cout << "REQUEST METHOD      = " << _method << std::endl;
	std::cout << "REQUEST REQUEST_URI = " << _request_uri << std::endl;
	std::cout << "REQUEST HTTPVERSION = " << _http_version << std::endl;
	std::cout << "REQUEST HOST        = " << _host << std::endl << std::endl;

	return (0);
};
