#ifndef LOCATION_HPP
# define LOCATION_HPP

# include <iostream>
# include <vector>
# include <string>
# include <set>

# include "Utils.hpp"

class Location
{

	public:

		Location(void);
		Location(std::string & uri);
		~Location(void);

		int		parse(std::vector<std::string> &);

	private:

		std::string					_uri;
		std::vector<std::string>	_index;
		bool						_get_allowed;
		bool						_post_allowed;
		bool						_delete_allowed;
		size_t						_redirection_code;
		std::string					_redirection_path;
		std::string					_root;
		bool						_directory_listing;
		std::string					_directory_file;
		std::string					_cgi;
		bool						_upload;
		std::string					_upload_path;

		int		set_allow_methods(std::vector<std::string> &, size_t &);
		int		set_redirection(std::vector<std::string> &, size_t &);
		int		set_index(std::vector<std::string> &, size_t &);
		int		set_root(std::vector<std::string> &, size_t &);
		int		set_directory_listing(std::vector<std::string> &, size_t &);
		int		set_directory_file(std::vector<std::string> &, size_t &);
		int		set_cgi(std::vector<std::string> &, size_t &);
		int		set_upload(std::vector<std::string> &, size_t &);
		int		set_upload_path(std::vector<std::string> &, size_t &);

	public:

		const std::string &					get_uri(void)				const;
		const bool &						get_allowed(void)			const;
		const bool &						post_allowed(void)			const;
		const bool &						delete_allowed(void)		const;
		const bool &						redirection(void)			const;
		const size_t &						get_redirection_code(void)	const;
		const std::string &					get_redirection_path(void)	const;
		const std::string &					root(void)					const;
		const std::vector<std::string> &	index(void)					const;
		const bool &						directory_listing(void)		const;
		const std::string &					get_directory_file(void)	const;
		const std::string &					cgi(void)					const;
		const bool &						is_cgi(void)				const; 	
		const bool &			   			upload_allowed(void)		const;
		const std::string &					get_upload_path(void)		const;

		bool						root_set;
		bool						directory_file_set;
		bool						directory_listing_set;
		bool						upload_set;
		bool						cgi_set;
		bool						upload_path_set;
		bool						redirection_set;
};

# endif
