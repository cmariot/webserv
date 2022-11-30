#include "Request.hpp"

// Au moins un des deux doit etre present dans le header de la requete pour qu'on ait un body.
bool	Request::body_in_this_request(void) const
{
	const std::multimap<string, string>::const_iterator	it_transfert_encoding
		= _header.find("Transfert-Encoding");
	const std::multimap<string, string>::const_iterator	it_content_length
		= _header.find("Content-Length");

	if (it_transfert_encoding != _header.end() || it_content_length != _header.end())
		return (true);
	return (false);
};

// Un peu de parsing sur la requete pour obtenir les informations qui nous interessent
int	Request::interpret(void)
{
	if (_header_is_ready == false)
	{
		size_t		i = 0;

		if (set_request_line(i))
			return (1);
		else if (set_method(i))
			return (1);
		else if (set_uri(i))
			return (1);
		else if (set_http_version(i))
			return (1);
		else if (set_header(i))
			return (1);
		else if (set_server_address())
			return (1);
		_header_is_ready = true;
	}

	if (body_in_this_request() && _body_is_ready == false)
	{
		// A modifier, doit renvoyer 1 si le body n'est pas complet
		if (get_content() == 0) // get_request_body()
			_body_is_ready = true;
	}
	else
		_body_is_ready = true;

	return (0);
};

// Renvoie true quand la requete est suffisante pour generer une reponse.
bool	Request::is_ready(void)
{
	interpret();
	if (_header_is_ready == true && _body_is_ready == true)
		return (true);
	return (false);
};
