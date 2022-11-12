#include "Webserver.hpp"

int		Webserver::get_server_directives(std::vector<std::string> & vector, size_t & i, size_t & begin, size_t & end)
{
	const size_t	vector_size = vector.size();
	int				nb_open_braces = 1;

	if (vector[i] != "server")
		return (error("unknown context :", vector[i].c_str()));
	else if (i + 1 >= vector.size() || vector[i + 1] != "{")
		return (error("server must have an opening brace."));
	i += 2;
	begin = i;
	while (i < vector_size && nb_open_braces != 0)
	{
		end = i;
		if (vector[i] == "{")
			++nb_open_braces;
		else if (vector[i] == "}")
			--nb_open_braces;
		if (nb_open_braces == INT_MAX || nb_open_braces == INT_MIN)
			return (error("int overflow."));
		if (nb_open_braces != 0)
			++i;
	}
	if (i >= vector_size)
		return (error("unclosed brace in the configuration file."));
	return (0);
};

int		Webserver::parse_server(std::vector<std::string> & vector)
{
	const size_t				vector_size = vector.size();
	size_t						begin = 0;
	size_t						end = 0;
	std::vector<std::string>	server_directives;

	print(INFO, "Looking for 'server' blocks in the configuration file.");
	for (size_t i = 0 ; i < vector_size && nb_of_servers < server.max_size() ; ++i)
	{
		if (get_server_directives(vector, i, begin, end))
			return (1);
		server_directives = std::vector<std::string>(vector.begin() + begin, vector.begin() + end);
		print(INFO, "Creating a new server context");
		server.push_back(Server());
		if (server[nb_of_servers++].parse(server_directives))
			return (1);
	}
	return (0);
};
