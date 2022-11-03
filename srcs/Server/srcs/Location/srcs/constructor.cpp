#include "Location.hpp"

Location::Location(std::string & uri) :
	uri(uri),
	get_method_allowed(false),
	post_method_allowed(false),
	delete_method_allowed(false),
	directory_listing(false),
	accept_uploads(false)
{
	return ;
};
