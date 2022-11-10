#include "Location.hpp"

int	Location::parse(std::vector<std::string> & vector)
{
	for (size_t i = 0 ; i < vector.size() ; i++)
	{
		if (vector[i] == "allow_methods")
		{
			print(INFO, "Parsing of the allow_methods directive in the server's location context.");
			if (set_allow_methods(vector, i))
				return (1);
		}
		else if (vector[i] == "redirection")
		{
			print(INFO, "Parsing of the redirection directive in the server's location context.");
			if (set_redirection(vector, i))
				return (1);
		}
		else if (vector[i] == "root")
		{
			print(INFO, "Parsing of the root directive in the server's location context.");
			if (set_root(vector, i))
				return (1);
		}
		else if (vector[i] == "index")
		{
			print(INFO, "Parsing of the index directive in the server's location context.");
			if (set_index(vector, i))
				return (1);
		}
		else if (vector[i] == "directory_listing")
		{
			print(INFO, "Parsing of the directory_listing directive in the server's location context.");
			if (set_directory_listing(vector, i))
				return (1);
		}
		else if (vector[i] == "directory_file")
		{
			print(INFO, "Parsing of the directory_file directive in the server's location context.");
			if (set_directory_file(vector, i))
				return (1);
		}
		else if (vector[i] == "cgi")
		{
			print(INFO, "Parsing of the cgi directive in the server's location context.");
			if (set_cgi(vector, i))
				return (1);
		}
		else if (vector[i] == "upload")
		{
			print(INFO, "Parsing of the upload directive in the server's location context.");
			if (set_upload(vector, i))
				return (1);
		}
		else if (vector[i] == "upload_path")
		{
			print(INFO, "Parsing of the upload_path directive in the server's location context.");
			if (set_upload_path(vector, i))
				return (1);
		}
		else
			return (error("Syntax error : Invalid directive in the location context :", vector[i]));
	}
	if (_index_set == false)
		_index.insert("index.html");
	return (0);
};
