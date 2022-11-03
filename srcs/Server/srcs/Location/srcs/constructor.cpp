#include "Location.hpp"

Location::Location(std::string & uri) :
	uri(uri),
	get_method_allowed(false),
	post_method_allowed(false),
	delete_method_allowed(false),
	redirection(false),
	redirection_code(0),
	directory_listing(false),
	upload(false)
{
	return ;
};
