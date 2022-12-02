#include "Response.hpp"

bool Response::has_content(void) const
{
	return (_request.has_body());
};

bool Response::content_too_large(void) const
{
	const double max_size = _server.get_max_size();

	if (max_size != 0)
	{
		// Depend de la taille du body de la requete. avant ou apres modifs ?
		//if (_request.get_body_size() >= max_size)
		//	return (true);
	}
	return (false);	
}
