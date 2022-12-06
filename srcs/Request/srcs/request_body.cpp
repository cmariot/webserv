#include "Request.hpp"

size_t		hex_to_unsigned_int( const string & hexadecimal)
{
	size_t 		decimal;
    stringstream sstream;

    sstream << std::hex << hexadecimal;
    sstream >> decimal;

    return decimal;
}

// To do : [] check eof
//		   [] clean commentaires

bool	Request::unchunk(void)
{
	// La longueur de transfert esr definie par l'utilisation du transfert de codage fragmente
	// Sauf si le message se termine en fermant la connexion
	// codage fragmente voir 3.6
	// Dans le sujet webserv : Just remember that, for chunked request, your server needs to unchunked
	// it and the CGI will expect EOF as end of the body.

	size_t pos = get_header_size();

	string size_chunk;
	string request_tmp;

	size_chunk = _request.substr(pos + 2, _request.find("\r\n", pos) - pos);

	// Let's concatanate all the chunk by calculating the size of each chunk and adding it to the request_tmp
	while (size_chunk != "0")
	{
		request_tmp += _request.substr(pos + size_chunk.size() + 2, hex_to_unsigned_int(size_chunk));
		pos = _request.find("\r\n", pos + size_chunk.size() + 2 + hex_to_unsigned_int(size_chunk)) + 2 ;
		size_chunk = _request.substr(pos, _request.find("\r\n", pos) - pos);
	}
	_request = _request.substr(0, get_header_size()) + request_tmp;

	cout << "REQUEST TMP : " << _request << endl;

	return (true);
};

// Reference : http://abcdrfc.free.fr/rfc-vf/pdf/rfc2616.pdf  Page 20
bool	Request::body_is_ready(void)
{
	std::multimap<string, string>::iterator	transfer_encoding	= _header.find("Transfer-Encoding");
	std::multimap<string, string>::iterator	content_length		= _header.find("Content-Length");
	std::multimap<string, string>::iterator	content_type		= _header.find("Content-Type");

	if (transfer_encoding != _header.end() && transfer_encoding->second != "identity") // (CAS 2 PDF)
	{
		cout << "we do enter here" << endl;
		// Chunk request
		// Verif qu'on ait le chunk de taille 0 final
		// Set un booleen sur _chunk = true

		return (unchunk());
	}
	else if (content_length != _header.end() && transfer_encoding == _header.end())
	{
		if (content_length->second == itostring(_request.size() - _header_size))
			return (true);
	}
	else if (content_type != _header.end() && content_type->second.find("multipart/byteranges") != std::string::npos) // (CAS 4 PDF)
	{
		// Boundary
		// A tester !!!
		std::string		content_type_value;
		std::string		boundary;
		std::string		final_boundary;

		content_type_value = content_type->second;
		boundary = content_type_value.substr((content_type_value.find("boundary=") + 9), std::string::npos);
		final_boundary = "--" + boundary + "--";
		if (_request.find(final_boundary) != string::npos)
		{
			//get_content();
			// A FAIRE : _body_size = _request.size() - _header_size;
			return (true);
		}
	}
	else
		return (true);
	return (false);
};

// La présence d’un corps de message dans une demande est signalée par l’inclusion d’un champ d’en-tête
// Content-Length ou Transfer-Encoding dans les en-têtes de message de la demande
bool	Request::body_in_this_request(void)
{
	if (_header.find("Content-Length") != _header.end() 
		|| _header.find("Transfer-Encoding") != _header.end())
	{
		_has_body = true;
		return (true);
	}
	else
		return (false);
};
