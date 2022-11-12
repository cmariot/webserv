#include "Error_page.hpp"

const int &	Error_page::get_code(void) const
{
	return (_code);
};

const bool &	Error_page::change_response(void) const
{
	return (_change_response);
};

const bool &	Error_page::specified_response(void) const
{
	return (_specified_response);
};

const int &	Error_page::get_changed_code(void) const
{
	return (_changed_response);
};

const std::string &	Error_page::get_path(void) const
{
	return (_path);
};
