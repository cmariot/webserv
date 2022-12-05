#include "Location.hpp"

const std::string &		Location::get_uri(void) const
{
	return (_uri);
};

const bool &	Location::get_allowed(void) const
{
	return (_get_allowed);
};

const bool &	Location::post_allowed(void) const
{
	return (_post_allowed);
};

const bool &	Location::delete_allowed(void) const
{
	return (_delete_allowed);
};

const bool &	Location::redirection(void) const
{
	return (redirection_set);
};

const size_t &	Location::get_redirection_code(void) const
{
	return (_redirection_code);
};

const std::string &		Location::get_redirection_path(void) const
{
	return (_redirection_path);
};

const std::string &		Location::root(void) const
{
	return (_root);
};

const std::vector<std::string> &	Location::index(void) const
{
	return (_index);
};

const bool &	Location::directory_listing(void) const
{
	return (_directory_listing);
};

const std::string &		Location::get_directory_file(void) const
{
	return (_directory_file);
};

const std::string &		Location::get_directory_file_path(void) const
{
	return (_directory_file_path);
};

const std::vector<std::string> &	Location::cgi_extensions(void) const
{
	return (_cgi_extensions);
};

const bool &	Location::upload_allowed(void) const
{
	return (_upload);
};

const std::string &		Location::get_upload_path(void) const
{
	return (_upload_path);
};

const bool &		Location::is_cgi(void) const
{
	return (cgi_set);
};
