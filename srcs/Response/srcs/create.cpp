#include "Response.hpp"

void	Response::create(void)
{
	if (_no_location)
		return (generate_error_page(400));
	if (uri_too_long())
		return (generate_error_page(414));
	if (method_not_implemented())
		return (generate_error_page(501));
	if (method_not_allowed())
		return (generate_error_page(405));
	if (expect_100_continue())
		return (generate_100_continue());
	if (has_content())
	{
		if (content_too_large())
			return (generate_error_page(413));
		// if (content_type_not_accepted())
		//	return (generate_error_page(415));
	}
	//if (request_block_not_ok())
	//	return (generate_error_page(400));
	return ;
};
