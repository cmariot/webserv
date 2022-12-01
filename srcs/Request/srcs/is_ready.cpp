#include "Request.hpp"
#include <stdlib.h>

// Reference : http://abcdrfc.free.fr/rfc-vf/pdf/rfc2616.pdf
// Page 20
bool	Request::body_is_complete(void)
{
	std::multimap<string, string>::iterator	transfert_encoding = _header.find("Transfert-Encoding");
	std::multimap<string, string>::iterator	content_length = _header.find("Content-Length");
	std::multimap<string, string>::iterator	content_type = _header.find("Content-Type");

	// CAS 1 ignore (seulement pour reponse)
	if (transfert_encoding != _header.end() && transfert_encoding->second != "identity")
	{
		// La longueur de transfert esr definie par l'utilisation du transfert de codage fragmente
		// Sauf si le message se termine en fermant la connexion
		// codage fragmente voir 3.6
		// Dans le sujet webserv : Just remember that, for chunked request, your server needs to unchunked
		// it and the CGI will expect EOF as end of the body.
		std::cout << "CAS 2" << std::endl;
		std::cout << transfert_encoding->second << std::endl;
	}
	else if (content_length != _header.end() && transfert_encoding == _header.end()) // Pas sur de cette condition, pourquoi dans on envoie plusieurs files ca passe la ???
	{
		// La valeur de content_length représente à la fois la longueur d’entité et la longueur de transfert
		std::cout << "CAS 3" << std::endl;
		if (content_length->second == itostring(_request.size() - _header_size))
			return (true);
	}
	else if (content_type != _header.end() && content_type->second.find("boundary") != std::string::npos)
	{
		// ce type de support auto délimitant définit la longueur de transfert
		std::cout << "CAS 4" << std::endl;
		std::string	boundary = content_type->second;
		std::cout << boundary << std::endl;
	}
	// Cas 5 gere par epoll
	return (false);
};

// La présence d’un corps de message dans une demande est signalée par l’inclusion d’un champ d’en-tête
// Content-Length ou Transfer-Encoding dans les en-têtes de message de la demande
bool	Request::body_in_this_request(void) const
{
	if (_header.find("Content-Length") != _header.end())
		return (true);
	else if (_header.find("Transfert-Encoding") != _header.end())
		return (true);
	else
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
		if (body_in_this_request())
		{
			if (body_is_complete())
				_body_is_ready = true;
		}
		else
			_body_is_ready = true;
	}
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
