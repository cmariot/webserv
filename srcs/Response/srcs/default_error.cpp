#include "Response.hpp"

int			Response::default_error(int code)
{
	std::map<int, std::string>::iterator	it = _status_code_map.find(code);
	if (it != _status_code_map.end()) // Si le code d'erreur est trouve dans la map
	{
		_body_response = "<h1>Error " + code;
		_body_response += " :</h1>\n";
		_body_response += "<h2>";
		_body_response += it->second;
		_body_response += "</h2>";
		return (0);
	}
	else
	{
		error("Unimplemented response error code");
		return (1);
	}
};
