#include "Directive_error_page.hpp"

void	Directive_error_page::set_error(int error)
{
	_error = error;
};

void	Directive_error_page::set_change_response(bool change)
{
	_change_response = change;
};

void	Directive_error_page::set_specified_response(bool specified)
{
	_specified_response = specified;
};

void	Directive_error_page::set_redirection(int redirection)
{
	_redirection = redirection;
};

void	Directive_error_page::set_path(std::string path)
{
	_path = path;
};
