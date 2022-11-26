#include "Location.hpp"

static int	get_file(std::string & _directory_file, const std::string & path)
{
	std::ifstream	file;
	std::string		line;

	print(INFO, "Opening the file", path.c_str());
	file.open(path.c_str(), std::ios_base::in);
	if (file.is_open() == false)
		return (error("Could not open the file", path.c_str()));
	try
	{
		_directory_file = "";
		while (std::getline(file, line))
			_directory_file += line;
		if (file.eof() == false)
		{
			file.close();
			return (error("while reading the file", path.c_str()));
		}
		file.close();
	}
	catch (std::ios_base::failure & exception)
	{
		file.close();
		return (error(exception.what(), "(getline in parse)"));
	}
	catch (std::bad_alloc & exception)
	{
		file.close();
		return (error(exception.what(), "(push_back in parse)"));
	}
	return (0);
};

int	Location::set_directory_file(std::vector<std::string> & vector, size_t & i)
{
	if (directory_file_set == true)
		return (error("Syntax error : Multiple directory_file directives."));
	if (invalid_directive_len(vector, i, ";", 3, 3))
		return (error("Syntax error : invalid directory_file directive."));
	if (get_file(_directory_file, vector[++i]))
		return (error("Invalid directory file."));
	_directory_file_path = vector[i];
	if (vector[++i] != ";")
		return (error("Syntax error : the directory_file directive doesn't ends by ';'."));
	directory_file_set = true;
	return (0);
};
