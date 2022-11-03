#include "Location.hpp"

Location::Location(std::string & uri) :
	_uri(uri),
	_get_method_allowed(false),
	_post_method_allowed(false),
	_delete_method_allowed(false),
	_redirection(false),
	_redirection_code(0),
	_directory_listing(false),
	_upload(false)
{
	return ;
};
