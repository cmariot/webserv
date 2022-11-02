#include "Error_page.hpp"

Error_page::Error_page(int & code, bool & change_response, bool & specified_response, int & response, std::string & path)
{
	set_error(code);
	set_change_response(change_response);
	set_specified_response(specified_response);
	set_redirection(response);
	set_path(path);
	return ;
};
