#include "Location.hpp"

std::string		Location::get_uri(void) const
{
	return (_uri);
};

bool	Location::get_get_method_allowed(void) const
{
	return (_get_method_allowed);
};

bool	Location::get_post_method_allowed(void) const
{
	return (_post_method_allowed);
};

bool	Location::get_delete_method_allowed(void) const
{
	return (_delete_method_allowed);
};

bool	Location::get_redirection(void) const
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

std::string		Location::get_root(void) const
{
	return (_root);
};

bool	Location::get_directory_listing(void) const
{
	return (_directory_listing);
};

std::string		Location::get_directory_file(void) const
{
	return (_directory_file);
};

std::string		Location::get_cgi(void) const
{
	return (_cgi);
};

bool	Location::get_upload(void) const
{
	return (_upload);
};

std::string		Location::get_upload_path(void) const
{
	return (_upload_path);
};
