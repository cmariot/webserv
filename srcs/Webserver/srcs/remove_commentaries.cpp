#include "Webserver.hpp"

// Remove the commentaries from the vector
int		Webserver::remove_commentaries(std::vector<std::string> & string_vector) const
{
	size_t	comment_pos;

	for (size_t i = 0 ; i < string_vector.size() ; ++i)
	{
		comment_pos = string_vector[i].find("#");
		if (comment_pos != std::string::npos
			&& (comment_pos == 0 || isblank(string_vector[i][comment_pos - 1])))
		{
			try
			{
				string_vector[i] = string_vector[i].substr(0, comment_pos);
			}
			catch (const std::bad_alloc & exception)
			{
				return (error(exception.what(), "(remove_commentaries)"));
			}
		}
	}
	return (0);
};
