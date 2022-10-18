#include "Webserver.hpp"

// Check the number of arguments,
// if the file can be opened and
// store the file content in a string vector.
// Next -> Get the server blocks
int	Webserver::parse(int argc, const char *argv[])
{
	std::fstream				configuration_file;
	std::string					line;
	std::vector<std::string>	string_vector;

	if (argc != 2)
		return (usage());
	else
	{
		configuration_file.open(argv[1]);
		if (configuration_file.is_open() == false)
			return (error("Cannot open the file", argv[1]));
		while (std::getline(configuration_file, line))
			string_vector.push_back(line);
		if (configuration_file.eof() == false)
		{
			configuration_file.close();
			return (error("while reading the file", argv[1]));
		}
		configuration_file.close();
		if (parse_configuration_file(string_vector))
			return (1);
	}
	return (0);
};
