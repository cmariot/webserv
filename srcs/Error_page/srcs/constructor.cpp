#include "Error_page.hpp"

Error_page::Error_page(int & code, bool & change_response, bool & specified_response, int & response, std::string & path) :
	_error(code),
	_change_response(change_response),
	_specified_response(specified_response),
	_redirection(response),
	_path(path)
{
	return ;
};
