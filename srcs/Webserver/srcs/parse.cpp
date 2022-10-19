#include "Webserver.hpp"

// Check the number of arguments,
// if the file can be opened and
// store the file content in a string vector.
// Next -> Get the server blocks
int	Webserver::parse(int argc, const char *argv[])
{
	std::ifstream				configuration_file;
	std::string					line;
	std::vector<std::string>	string_vector;

	if (argc != 2)
		return (usage());
	configuration_file.open(argv[1], std::ios_base::in);
	if (configuration_file.is_open() == false)
		return (error("Could not open the file", argv[1]));
	try
	{
		while (std::getline(configuration_file, line))
			string_vector.push_back(line);
		if (configuration_file.eof() == false)
		{
			configuration_file.close();
			return (error("while reading the file", argv[1]));
		}
		configuration_file.close();
		if (string_vector.size() == 0)
			return (error("The configuration file is empty.", NULL));
	}
	catch (std::ios_base::failure & exception)
	{
		return (error(exception.what(), "(getline in parse)"));
	}
	catch (std::bad_alloc & exception)
	{
		return (error(exception.what(), "(push_back in parse)"));
	}
	if (parse_configuration_file(string_vector))
		return (1);
	return (0);
};
