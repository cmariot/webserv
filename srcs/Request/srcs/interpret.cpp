#include "Request.hpp"

int	Request::host_to_address(void)
{
	size_t	pos;

	pos = host.rfind(":");
	if (pos != std::string::npos)
	{
		request_address.first = host.substr(0, pos);
		request_address.second = set_port(host.substr(pos + 1));
	}
	else
	{
		if (only_digit(host))
		{
			request_address.first = "0.0.0.0";
			request_address.second = set_port(host);
		}
		else
		{
			request_address.first = host;
			request_address.second = 8080;
		}
	}
	return (0);
};

// 2eme ligne de la requete,
// nous donne des informations sur le serveur auquel on va envoyer la reponse
int	Request::get_host(void)
{
	size_t	pos = 0;

	host.clear();
	pos = request.find("Host:");
	if (pos == std::string::npos)
		return (error("No Host in the request"));
	pos += strlen("Host:");
	while (pos < request.size() && request[pos] == ' ')
		++pos;
	while (pos < request.size())
	{
		if (request[pos] == '\n' || request[pos] == '\r' || request[pos] == ' ')
			break ;
		host += request[pos++];
	}
	if (host.empty())
		return (error("No Host in the request"));
	return (0);
};

// 3eme partie de la Request-line : Version HTTP
int	Request::get_http_version(std::string & request_line, size_t & i)
{
	http_version.clear();
	while (i < request_line.size() && request_line[i] != '\r')
		http_version += request_line[i++];
	if (uri.empty())
		return (error("Invalid _http_version in the request line."));
	return (0);
};

// 2nde partie de la Request-line : l'URI
int	Request::get_request_uri(std::string & request_line, size_t & i)
{
	uri.clear();
	while (i < request_line.size())
	{
		if (request_line[i] == ' ')
			break ;
		uri += request_line[i++];
	}
	while (request_line[i] == ' ')
		i++;
	if (uri.empty())
		return (error("Invalid request_uri in the request line."));
	return (0);
};

// 1ere partie de la Request-line : Methode
int	Request::get_method(std::string & request_line, size_t & i)
{
	method.clear();
	while (i < request_line.size())
	{
		if (request_line[i] == ' ')
			break ;
		method += request_line[i++];
	}
	while (request_line[i] == ' ')
		i++;
	if (method.empty())
		return (error("Invalid method in the request line."));
	return (0);
};


# define CRLF		"\r\n"
# define CRLF_LEN	 2

// La request line est la 1ere ligne de la requete,
// (sauf si des CRLF sont en debut de header, dans ce cas ils sont skip)
// Request-Line = Method SP Request-URI SP HTTP-Version CRLF
int	Request::get_request_line(std::string & request_line, size_t & i)
{
	while (i + 1 < request.size()
			&& request[i] == '\r'
			&& request[i + 1] == '\n')
		i += 2;

	const size_t	pos = request.find(CRLF, i);

	if (pos == std::string::npos)
		// status code ?
		return (error("Invalid request line, no CRLF."));
	
	request_line = request.substr(i, pos + CRLF_LEN);
	if (request_line.empty())
		// status code ?
		return (error("Empty request line."));
	return (0);
};

// Un peu de parsing sur la requete pour obtenir les informations qui nous interessent
int	Request::interpret(void)
{
	std::string		request_line;
	size_t			i = 0;

	if (get_request_line(request_line, i))
		return (1);
	else if (get_method(request_line, i))
		return (1);
	else if (get_request_uri(request_line, i))
		return (1);
	else if (get_http_version(request_line, i))
		return (1);
	else if (get_host())
		return (1);
	else if (host_to_address())
		return (1);
	else if (method == "POST")
		get_content();
	return (0);
};
