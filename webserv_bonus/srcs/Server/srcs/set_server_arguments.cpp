#include "Server.hpp"

int	Server::set_server_arguments(std::vector<std::string> & token_vector, std::string ip, size_t port)
{
	(void)token_vector;
	this->ip = ip;
	this->port = port;
	//for (size_t i = 0 ; i < token_vector.size() ; ++i)
	//{
	//	std::cout << "TOKEN[" << i << "] = " << token_vector[i] << std::endl;
	//	if (token_vector[i] == "listen")
	//	{
	//		
	//	}
	//}
	return (0);
};
