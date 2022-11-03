#include "Error_page.hpp"

int			Error_page::get_error(void)					const
{
	return (_error);
};

bool		Error_page::get_change_response(void)		const
{
	return (_change_response);
};

bool		Error_page::get_specified_response(void)	const
{
	return (_specified_response);
};

int			Error_page::get_redirection(void)			const
{
	return (_redirection);
};

std::string	Error_page::get_path(void)					const
{
	return (_path);
};
