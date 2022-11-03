#include "Location.hpp"

int	Location::parse(std::vector<std::string> & vector)
{
	for (size_t i = 0 ; i < vector.size() ; i++)
	{
		if (vector[i] == "allow_methods")
		{
			if (set_allow_methods(vector, i))
				return (1);
		}
		else if (vector[i] == "redirection")
		{
			if (set_redirection(vector, i))
				return (1);
		}
		else if (vector[i] == "root")
		{
			if (set_root(vector, i))
				return (1);
		}
		else if (vector[i] == "directory_listing")
		{
			if (set_directory_listing(vector, i))
				return (1);
		}
		else if (vector[i] == "directory_file")
		{
			if (set_directory_file(vector, i))
				return (1);
		}
		else if (vector[i] == "cgi")
		{
			if (set_cgi(vector, i))
				return (1);
		}
		else if (vector[i] == "upload")
		{
			if (set_upload(vector, i))
				return (1);
		}
		else if (vector[i] == "upload_path")
		{
			if (set_upload_path(vector, i))
				return (1);
		}
		else
			return (error("Syntax error : Invalid directive in the location context :", vector[i]));
	}
	return (0);
};
