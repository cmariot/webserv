#include "Server.hpp"

int	Server::set_server_arguments(std::vector<std::string> & token_vector)
{
	// default already set
	for (size_t i = 0 ; i < token_vector.size() ; i++)
	{
		if (token_vector[i] == "listen") // OK
		{
			if (parse_listen_directive(token_vector, i))
				return (1);
		}
		else if (token_vector[i] == "server_name") // A FAIRE
		{
			if (parse_server_name_directive(token_vector, i))
				return (1);
		}
		else if (token_vector[i] == "error_page") // OK
		{
			if (parse_error_page_directive(token_vector, i))
				return (1);
		}
		else if (token_vector[i] == "client_max_body_size") // OK
		{
			if (parse_client_max_body_size_directive(token_vector, i))
				return (1);
		}
		else if (token_vector[i] == "root") // OK
		{
			if (parse_root_directive(token_vector, i))
				return (1);
		}
		else if (token_vector[i] == "index") // OK
		{
			if (parse_index_directive(token_vector, i))
				return (1);
		}
		else if (token_vector[i] == "location") // A FAIRE
		{
			if (parse_location_context(token_vector, i))
				return (1);
		}
		// voir si il faut rajouter des cas
		else
			return (error("Invalid syntax in the configuration file near", token_vector[i].c_str()));
	}
	// verifications
	return (0);
};
