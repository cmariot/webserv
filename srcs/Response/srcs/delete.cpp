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

	print(INFO, ("Trying to delete the file " + _path).c_str());

	if (is_a_file(_path) == false && is_a_dir(_path) == false)
		return (generate_error_page(404));	// Not found
	if (has_write_rights(_path) == false)
		return (generate_error_page(403));	// Forbidden
	if (remove(_path.c_str()) != 0)
		return (generate_error_page(500));	// Internal error
	return (generate_error_page(200));		// File removed
};
