#ifndef LOCATION_HPP
# define LOCATION_HPP

# include <iostream>
# include <vector>
# include <string>

class Location
{
	public:

		Location(std::string & uri);
		~Location(void);

		int	parse(std::vector<std::string> &);

	private:

		std::string		_uri;
		bool			_get_method_allowed;
		bool			_post_method_allowed;
		bool			_delete_method_allowed;
		bool			_redirection;
		size_t			_redirection_code;
		std::string		_redirection_path;
		std::string		_root;
		bool			_directory_listing;
		std::string		_directory_file;
		std::string		_cgi;
		bool			_upload;
		std::string		_upload_path;

		int		set_allow_methods(std::vector<std::string> &, size_t &);
		int		set_redirection(std::vector<std::string> &, size_t &);
		int		set_root(std::vector<std::string> &, size_t &);
		int		set_directory_listing(std::vector<std::string> &, size_t &);
		int		set_directory_file(std::vector<std::string> &, size_t &);
		int		set_cgi(std::vector<std::string> &, size_t &);
		int		set_upload(std::vector<std::string> &, size_t &);
		int		set_upload_path(std::vector<std::string> &, size_t &);

		int		error(std::string error) const;
		int		error(std::string error, std::string complement) const;
		bool	invalid_directive_len(std::vector<std::string> &, size_t, std::string, size_t, size_t) const;
};

# endif
