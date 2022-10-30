#include "Directive_error_page.hpp"

int		Directive_error_page::get_error(void) const
{
	return (_error);
};

bool	Directive_error_page::get_change_response(void) const
{
	return (_change_response);
};

bool	Directive_error_page::get_specified_response(void) const
{
	return (_specified_response);
};

int		Directive_error_page::get_redirection(void) const
{
	return (_redirection);
};

std::string	Directive_error_page::get_path(void) const
{
	return (_path);
};
