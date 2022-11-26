#include "Error_page.hpp"

int	Error_page::get_file(void)
{
	std::ifstream	error_page;
	std::string		line;

	print(INFO, "Opening the file", _path.c_str());
	error_page.open(_path.c_str(), std::ios_base::in);
	if (error_page.is_open() == false)
		return (error("Could not open the file", _path.c_str()));
	try
	{
		_file_content = "";
		while (std::getline(error_page, line))
			_file_content += line;
		if (error_page.eof() == false)
		{
			error_page.close();
			return (error("while reading the file", _path.c_str()));
		}
		error_page.close();
	}
	catch (std::ios_base::failure & exception)
	{
		error_page.close();
		return (error(exception.what(), "(getline in parse)"));
	}
	catch (std::bad_alloc & exception)
	{
		error_page.close();
		return (error(exception.what(), "(push_back in parse)"));
	}
	return (0);
};
