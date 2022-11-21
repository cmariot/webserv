#include "Error_page.hpp"

// error_page 404 [= [403]] path

Error_page::Error_page(int & code, bool & change_response, bool & specified_response, int & response, std::string & path) :
	_code(code),
	_change_response(change_response),
	_specified_response(specified_response),
	_changed_response(response),
	_path(path)
{
	return ;
};
