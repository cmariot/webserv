#include "Server.hpp"

int	Server::parse(std::vector<std::string> & vector)
{
	if (vector.empty())
		return (error("Syntax error : empty server in the configuration file."));
	for (size_t i = 0 ; i < vector.size() ; i++)
	{
		if (vector[i] == "listen")
		{
			if (set_listen(vector, i))
				return (1);
		}
		else if (vector[i] == "server_names")
		{
			if (set_server_names(vector, i))
				return (1);
		}
		else if (vector[i] == "error_page")
		{
			if (set_error_pages(vector, i))
				return (1);
		}
		else if (vector[i] == "client_max_body_size")
		{
			if (set_client_max_body_size(vector, i))
				return (1);
		}
		else if (vector[i] == "location")
		{
			if (set_location(vector, i))
				return (1);
		}
		else
			return (error("Syntax error : Unknown directive :", vector[i].c_str()));
	}
	return (0);
};
