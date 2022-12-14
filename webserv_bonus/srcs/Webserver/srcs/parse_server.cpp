// OK untill the servers initialization
#include "Webserver.hpp"

int		Webserver::parse_server(std::vector<std::string> & tokens_vector)
{
	const size_t	vector_size = tokens_vector.size();
	size_t			begin = 0;
	size_t			end = 0;
	int				nb_open_braces;

	std::vector<std::string>	ip;
	size_t						port;

	ip.push_back("127.0.0.1");
	ip.push_back("127.0.0.2");
	ip.push_back("127.0.0.3");
	port = 8080;

	for (size_t i = 0 ; i < vector_size ; ++i)
	{
		if (tokens_vector[i] != "server")
			return (error("unknown context :", tokens_vector[i].c_str()));
		else if (i + 1 >= vector_size || tokens_vector[i + 1] != "{")
			return (error("server must have an opening brace.", NULL));
		i += 2;
		begin = i;
		nb_open_braces = 1;
		while (nb_open_braces != 0 && i < vector_size)
		{
			end = i;
			if (tokens_vector[i] == "{")
				++nb_open_braces;
			else if (tokens_vector[i] == "}")
				--nb_open_braces;
			if (nb_open_braces != 0)
				++i;
			if (nb_open_braces == INT_MAX || nb_open_braces == INT_MIN)
				return (error("int overflow.", NULL));
		}
		if (i >= vector_size)
			return (error("unclosed brace in the configuration file.", NULL));

		server.push_back(Server());
		std::vector<std::string>	arguments_vector(tokens_vector.begin() + begin, tokens_vector.begin() + end);
		server[nb_of_servers].set_server_arguments(arguments_vector, ip[nb_of_servers], port);

		++nb_of_servers;
	}
	return (0);
}
