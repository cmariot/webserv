#include "Response.hpp"

// 127.0.0.1:8080 : OK
// 127.0.0.1:8080/index.html : OK
// 127.0.0.1:8080/index.html/ : On le gere ? Peut etre avec une redirection ?

static	bool	is_a_file(const std::string & path)
{
	struct stat path_stat;

	bzero(&path_stat, sizeof(path_stat));
	if (stat(path.c_str(), &path_stat) != 0)
		return (false);
	return (S_ISREG(path_stat.st_mode));
};

int	Response::path_construction(void)
{
	//std::cout << "CONSTRUCTION DU PATH A PARTIR DE :" << std::endl;
	//std::cout << "- location.uri : " << _location.get_uri() << std::endl;
	//std::cout << "- location.root : " << _location.root() << std::endl;
	//std::cout << "- location.index : " << _location.index()[0] << std::endl;
	// std::cout << "- request.uri : " << _request.uri << std::endl;

	std::string	path;

	_dir = false;
	_file_path = _request.uri;
	_file_path.replace(0, _location.get_uri().size(), _location.root());
	if (is_a_file(_file_path) == true)
	{
		return (0);
	}
	for (size_t i = 0 ; i < _location.index().size() ; ++i)
	{
		path = _file_path + _location.index()[i];
		if (is_a_file(path) == true)
		{
			_file_path = path;
			return (0);
		}
	}
	if (is_a_directory(_file_path) == true)
	{
		_dir = true;
		return (0);
	}
	return (1);
};
