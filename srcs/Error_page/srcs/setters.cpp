#include "Error_page.hpp"

void	Error_page::set_error(int error)
{
	_error = error;
};

void	Error_page::set_change_response(bool change)
{
	_change_response = change;
};

void	Error_page::set_specified_response(bool specified)
{
	_specified_response = specified;
};

void	Error_page::set_redirection(int redirection)
{
	_redirection = redirection;
};

void	Error_page::set_path(std::string path)
{
	_path = path;
};
