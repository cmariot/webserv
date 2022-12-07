#include "Location.hpp"

int		Location::set_upload_path(std::vector<std::string> & vector, size_t & i)
{
	if (upload_path_set == true)
		return (error("Synax error : Multiple upload_path directives for the same location context"));
	if (invalid_directive_len(vector, i, ";", 3, 3))
		return (error("Syntax error : invalid upload_path directive len."));
	_upload_path = vector[++i];
	if (_upload_path.empty() == false)
	{
		if (_upload_path[0] == '/')
			return (error("Syntax error : The upload_path must be relative to the location_root."));
		else if (_upload_path[0] != '.')
			_upload_path = "./" + _upload_path;
	}
	if (vector[++i] != ";")
		return (error("Syntax error : the upload_path directive doesn't ends by ';'."));
	upload_path_set = true;
	return (0);
};
