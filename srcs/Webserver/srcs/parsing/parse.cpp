#include "Webserver.hpp"

int	check_extension(const char *filename, const char *extension)
{
	size_t	filename_len;
	size_t	extension_len;

	filename_len = strlen(filename);
	extension_len = strlen(extension);
	if (filename_len-- < extension_len--)
		return (1);
	while (extension_len + 1 != 0)
		if (filename[filename_len--] != extension[extension_len--])
			return (1);
	return (0);
}

int	Webserver::get_file(const char *filename, std::vector<std::string> & vector)
{
	std::ifstream	configuration_file;
	std::string		line;

	print(INFO, "Opening the file", filename);
	configuration_file.open(filename, std::ios_base::in);
	if (configuration_file.is_open() == false)
		return (error("Could not open the file", filename));
	try
	{
		while (std::getline(configuration_file, line))
			vector.push_back(line);
		if (configuration_file.eof() == false)
		{
			configuration_file.close();
			return (error("while reading the file", filename));
		}
		configuration_file.close();
		if (vector.size() == 0)
			return (error("The configuration file is empty."));
	}
	catch (std::ios_base::failure & exception)
	{
		configuration_file.close();
		return (error(exception.what(), "(getline in parse)"));
	}
	catch (std::bad_alloc & exception)
	{
		configuration_file.close();
		return (error(exception.what(), "(push_back in parse)"));
	}
	return (0);
};

int	Webserver::check_arguments(int argc, const char *argv[])
{
	print(INFO, "Checking the webserv's arguments");
	if (argc > 2)
		return (usage());
	else if (argc == 1)
		argv[1] = "configuration_files/default.conf";
	else if (check_extension(argv[1], ".conf"))
		return (error("The configuration file must have the '.conf' extension."));
	return (0);
}

const char **Webserver::get_env(void) const
{
	return (env);
};

void	Webserver::set_env(const char **env)
{
	env = env;
	return ;
};

// Check the number of arguments,
// if the file can be opened and
// store the file content in a string vector.
int	Webserver::parse(const int argc, const char *argv[], const char *env[])
{
	std::vector<std::string>	vector;

	print(INFO, "Webserv is starting ...");
	if (check_arguments(argc, argv))
		return (1);
	if (get_file(argv[1], vector))
		return (1);
	if (parse_configuration_file(vector))
		return (1);
	set_env(env);
	print(INFO, "The configuration file seems to be ok.");
	print_config();
	return (0);
};
