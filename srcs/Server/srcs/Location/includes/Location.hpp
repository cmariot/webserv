#ifndef LOCATION_HPP
# define LOCATION_HPP

# include <iostream>
# include <vector>
# include <string>

class Location
{
	public:

		std::string				uri;
		bool					get_method_allowed;
		bool					post_method_allowed;
		bool					delete_method_allowed;
		std::vector<void *>		redirections;
		std::string				root;
		bool					directory_listing;
		std::string				directory_file;
		bool					accept_uploads;
		std::string				upload_path;

		Location(std::string & uri);
		~Location();

		int	parse_location(std::vector<std::string> &);

	private:

		int		parse_allow_methods(std::vector<std::string> &, size_t &);
		int		parse_redirection(std::vector<std::string> &, size_t &);
		int		parse_root(std::vector<std::string> &, size_t &);
		int		parse_directory_listing(std::vector<std::string> &, size_t &);
		int		parse_directory_file(std::vector<std::string> &, size_t &);
		int		parse_cgi(std::vector<std::string> &, size_t &);

		int		error(std::string error);
		int		error(std::string error, std::string complement);
		bool	invalid_directive_len(std::vector<std::string> &, size_t, std::string, size_t, size_t);
};

# endif
