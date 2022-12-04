#include "Response.hpp"

bool	has_write_rights(const string & path)
{
	struct stat	file_stat;

	if (stat(path.c_str(), &file_stat))
		return (false);
	if (file_stat.st_mode & S_IWUSR)
		return (true);
	return (false);
};

void    Response::delete_method(void)
{
	_path = _request.get_uri();
	_path.replace(0, _location.get_uri().size(), _location.root());

	if (is_a_file(_path))
	{
		if (has_write_rights(_path) == false)
		{
			if (unlink(_path.c_str()) == 0)			// On teste quand meme
				return (generate_error_page(200));	// OK
			return (generate_error_page(403));		// Permission denied
		}
		if (unlink(_path.c_str()) != 0)
			return (generate_error_page(403));		// Permission denied
		return (generate_error_page(200));			// File removed
	}
	else if (is_a_dir(_path))
	{
		if (has_write_rights(_path) == false)
		{
			if (rmdir(_path.c_str()) == 0)			// On teste quand meme
				return (generate_error_page(200));	// OK
			return (generate_error_page(403));		// Permission denied
		}
		if (rmdir(_path.c_str()) != 0)
			return (generate_error_page(403));		// Permissions denied
		return (generate_error_page(200));			// Dir removed
	}
	else
		return (generate_error_page(404));			// not found
};
