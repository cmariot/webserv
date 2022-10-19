#include "Server.hpp"

int	Server::set_server_arguments(std::vector<std::string> & token_vector)
{
	for (size_t i = 0 ; i < token_vector.size() ; ++i)
	{
		std::cout << "TOKEN[" << i << "] = " << token_vector[i] << std::endl;
	}
	return (0);
};
