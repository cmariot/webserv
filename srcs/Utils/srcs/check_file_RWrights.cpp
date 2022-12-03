#include "Utils.hpp"

bool	check_file_rights(string	&path)
{
	struct stat	file_stat;

	if (stat(path.c_str(), &file_stat) == 0)
	{	
		if (file_stat.st_mode & S_IRUSR && file_stat.st_mode & S_IWUSR)
			return (true);
		else
			return (false);
	}
    return (false);
}
