#include "Utils.hpp"

bool	is_a_dir(const std::string & path)
{
	struct stat	path_stat;

	bzero(&path_stat, sizeof(path_stat));
	stat(path.c_str(), &path_stat);
	return (S_ISDIR(path_stat.st_mode));
};

bool	is_a_file(const std::string & path)
{
	struct stat path_stat;

	bzero(&path_stat, sizeof(path_stat));
	if (stat(path.c_str(), &path_stat) != 0)
		return (false);
	return (S_ISREG(path_stat.st_mode));
};

bool	check_file_rights(const string & path)
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
