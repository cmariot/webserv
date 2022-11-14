#include "Response.hpp"

int	Response::path_construction(void)
{
	std::cout << "CONSTRUCTION DU PATH A PARTIR DE :" << std::endl;
	std::cout << "- location.root : " << _location.root() << std::endl;
	std::cout << "- location.index : " << _location.index()[0] << std::endl;
	std::cout << "- request.uri : " << _request.uri << std::endl;
	_file_path = _location.root() + _location.index()[0];
	std::cout << _file_path << std::endl;
	return (0);
};
