#include "Location.hpp"

int	Location::parse_location(std::vector<std::string> & vector)
{
	for (size_t i = 0 ; i < vector.size() ; i++)
	{
		if (vector[i] == "allow_methods")
		{
			if (parse_allow_methods(vector, i))
				return (1);
		}
		else if (vector[i] == "redirection")
		{
			if (parse_redirection(vector, i))
				return (1);
		}
		else if (vector[i] == "root")
		{
			if (parse_root(vector, i))
				return (1);
		}
		else if (vector[i] == "directory_listing")
		{
			if (parse_directory_listing(vector, i))
				return (1);
		}
		else if (vector[i] == "directory_file")
		{
			if (parse_directory_file(vector, i))
				return (1);
		}
		else if (vector[i] == "cgi")
		{
			if (parse_cgi(vector, i))
				return (1);
		}
		else if (vector[i] == "upload")
		{
			if (parse_upload(vector, i))
				return (1);
		}
		else if (vector[i] == "upload_path")
		{
			if (parse_upload_path(vector, i))
				return (1);
		}
		else
			return (error("Syntax error : Invalid directive in the location context :", vector[i]));
	}
	return (0);
};
