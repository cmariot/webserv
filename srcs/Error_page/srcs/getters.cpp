#include "Error_page.hpp"

int	Error_page::get_code(void) const
{
	return (_code);
};

bool	Error_page::change_response(void) const
{
	return (_change_response);
};

bool	Error_page::specified_response(void) const
{
	return (_specified_response);
};

int	Error_page::get_changed_code(void) const
{
	return (_changed_response);
};

std::string	Error_page::get_path(void) const
{
	return (_path);
};
