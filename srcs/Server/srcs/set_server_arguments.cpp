#include "Server.hpp"

int	Server::set_server_arguments(std::vector<std::string> & token_vector)
{
	std::cout << std::endl << "server" << std::endl << "{" << std::endl;
	for (size_t i = 0 ; i < token_vector.size() ; i++)
	{
		if (token_vector[i] == "listen")
		{
			if (parse_listen_directive(token_vector, i))
				return (1);
		}
		else if (token_vector[i] == "server_names")
		{
			if (parse_server_names_directive(token_vector, i))
				return (1);
		}
		else if (token_vector[i] == "error_page")
		{
			if (parse_error_page_directive(token_vector, i))
				return (1);
		}
		else if (token_vector[i] == "client_max_body_size")
		{
			if (parse_client_max_body_size_directive(token_vector, i))
				return (1);
		}
		else if (token_vector[i] == "location")
		{
			if (parse_location_context(token_vector, i))
				return (1);
		}
		else
			return (error("Syntax error : Unknown directive :", token_vector[i].c_str()));
	}
	std::cout << "}" << std::endl << std::endl;
	return (0);
};
