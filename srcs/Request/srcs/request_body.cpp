#include "Request.hpp"

bool	Request::unchunk(void)
{
	// La longueur de transfert esr definie par l'utilisation du transfert de codage fragmente
	// Sauf si le message se termine en fermant la connexion
	// codage fragmente voir 3.6
	// Dans le sujet webserv : Just remember that, for chunked request, your server needs to unchunked
	// it and the CGI will expect EOF as end of the body.
	return (false);
};

// Reference : http://abcdrfc.free.fr/rfc-vf/pdf/rfc2616.pdf  Page 20
bool	Request::body_isnot_complete(void)
{
	std::multimap<string, string>::iterator	transfert_encoding = _header.find("Transfert-Encoding");
	std::multimap<string, string>::iterator	content_length = _header.find("Content-Length");
	std::multimap<string, string>::iterator	content_type = _header.find("Content-Type");

	if (transfert_encoding != _header.end() && transfert_encoding->second != "identity")
	{
		std::cout << "CAS 2 : unchunk" << std::endl;
	
		return (unchunk());
	}
	else if (content_length != _header.end() && transfert_encoding == _header.end() && get_method() != "POST")
	{
		std::cout << "CAS 3 : utilisation des boundary " << get_method() << std::endl;
		if (content_length->second == itostring(_request.size() - _header_size))
			return (true);
	}
	else if (content_type != _header.end() && content_type->second.find("boundary") != std::string::npos)
	{
		std::cout << "CAS 4 : utilisation des boundary" << std::endl;
		// ce type de support auto délimitant définit la longueur de transfert
		std::string	boundary = content_type->second;
		boundary = boundary.substr((boundary.find("=") + 1), boundary);
		cout << boundary << endl;
		get_content();
		return (false);
	}
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
