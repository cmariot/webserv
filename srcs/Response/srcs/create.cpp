#include "Response.hpp"

void	Response::create(void)
{
	if (uri_too_long())
		return (generate_error_page(414));

	return ;
};
