#include "Webserver.hpp"

// Remove the commentaries from the string vector
// A commentary begins with the '#' character if '#'
// is at the begining of a line or the character before
// the '#' is a blank character and ends at the end of the line.
//
// Examples :
//	# comment
//	not a comment #but this is a comment
//	foo#not_a_comment

int		Webserver::remove_commentaries(std::vector<std::string> & string_vector) const
{
	size_t		comment_pos;
	std::string	tmp;

	for (size_t i = 0 ; i < string_vector.size() ; ++i)
	{
		comment_pos = string_vector[i].find("#");
		if (comment_pos != std::string::npos
			&& (comment_pos == 0 || isblank(string_vector[i][comment_pos - 1]) == true))
		{
			try
			{
				tmp = string_vector[i].substr(0, comment_pos);
				string_vector[i] = tmp;
			}
			catch (const std::out_of_range & exception)
			{
				return (error(exception.what(), "(remove_commentaries)"));
			}
			catch (const std::bad_alloc & exception)
			{
				return (error(exception.what(), "(remove_commentaries)"));
			}
		}
	}
	return (0);
};
