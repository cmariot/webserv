#include "Location.hpp"

std::string		Location::get_uri(void) const
{
	return (_uri);
};

bool	Location::get_allowed(void) const
{
	return (_get_allowed);
};

bool	Location::post_allowed(void) const
{
	return (_post_allowed);
};

bool	Location::delete_allowed(void) const
{
	return (_delete_allowed);
};

bool	Location::redirection(void) const
{
	return (_redirection);
};

size_t	Location::get_redirection_code(void) const
{
	return (_redirection_code);
};

std::string		Location::get_redirection_path(void) const
{
	return (_redirection_path);
};

std::string		Location::root(void) const
{
	return (_root);
};

std::vector<std::string>	Location::index(void) const
{
	return (_index);
};

bool	Location::directory_listing(void) const
{
	return (_directory_listing);
};

std::string		Location::get_directory_file(void) const
{
	return (_directory_file);
};

std::string		Location::cgi(void) const
{
	return (_cgi);
};

bool	Location::upload_allowed(void) const
{
	return (_upload);
};

std::string		Location::get_upload_path(void) const
{
	return (_upload_path);
};
