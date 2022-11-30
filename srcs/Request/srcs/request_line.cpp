#include "Request.hpp"

// 3eme partie de la Request-line : Version HTTP
int	Request::set_http_version(size_t & i)
{
	size_t	version_len = 0;

	while (i < _request_line.size() && _request_line[i] == ' ')
		++i;
	while (i + version_len < _request_line.size())
	{
		if (_request_line[i + version_len] == ' ')
			break ;
		++version_len;
	}
	_http_version = _request_line.substr(i, version_len);
	i += version_len;
	if (_http_version.empty())
		return (error("Invalid HTTP version in the request line."));
	return (0);
};

// 2nde partie de la Request-line : l'URI
int	Request::set_uri(size_t & i)
{
	size_t	uri_len = 0;

	while (i < _request_line.size() && _request_line[i] == ' ')
		++i;
	while (i + uri_len < _request_line.size())
	{
		if (_request_line[i + uri_len] == ' ')
			break ;
		++uri_len;
	}
	_uri = _request_line.substr(i, uri_len);
	i += uri_len;
	if (_uri.empty())
		return (error("Invalid uri in the request line."));
	return (0);
};

// 1ere partie de la Request-line : Methode
int	Request::set_method(size_t & i)
{
	size_t	method_len = 0;

	while (i < _request_line.size() && _request_line[i] == ' ')
		++i;
	while (i + method_len < _request_line.size())
	{
		if (_request_line[i + method_len] == ' ')
			break ;
		++method_len;
	}
	_method = _request_line.substr(i, method_len);
	i += method_len;
	if (_method.empty())
		return (error("Invalid method in the request line."));
	return (0);
};

// La request line est la 1ere ligne de la requete,
// (sauf si des CRLF sont en debut de header, dans ce cas ils sont skip)
// Request-Line = Method SP Request-URI SP HTTP-Version CRLF
int	Request::set_request_line(size_t & i)
{
	// Skip begining CRLF
	while (i + 1 < _request.size()
			&& _request[i] == '\r'
			&& _request[i + 1] == '\n')
		i += 2;

	const size_t	pos = _request.find(CRLF, i);

	if (pos == std::string::npos)
		return (error("Invalid request line, missing CRLF."));
	_request_line = _request.substr(i, pos);
	if (_request_line.empty())
		return (error("Empty request line."));
	return (0);
};
