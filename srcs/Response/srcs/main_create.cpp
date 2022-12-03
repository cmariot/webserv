#include "Response.hpp"

void	Response::main_create(void)
{
	if (_no_location)
		return (generate_error_page(404));
	if (uri_too_long())
		return (generate_error_page(414));
	if (header_too_large())
		return (generate_error_page(431));
	if (method_not_implemented())
		return (generate_error_page(501));
	if (method_not_allowed())
		return (generate_error_page(405));
	if (expect_100_continue())
		return (generate_100_continue());
	if (has_content())
	{
		// decoder ici ?
		if (content_too_large()) // Voir taille body
			return (generate_error_page(413));
		// if (content_type_not_accepted())
		//	return (generate_error_page(415));
	}
	if (request_block_not_ok()) // voir ce qu'on met dedans
		return (generate_error_page(400));

	if (_request.get_method() == "GET")
		return (get_method());
	else if (_request.get_method() == "POST")
		return (post_method());
	else if (_request.get_method() == "DELETE")
		return (delete_method());

	return ;
};
