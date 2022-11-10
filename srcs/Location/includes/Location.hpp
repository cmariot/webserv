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
		bool						_redirection;
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

		std::string					get_uri(void)				const;
		bool						get_allowed(void)			const;
		bool						post_allowed(void)			const;
		bool						delete_allowed(void)		const;
		bool						redirection(void)			const;
		size_t						get_redirection_code(void)	const;
		std::string					get_redirection_path(void)	const;
		std::string					root(void)					const;
		std::vector<std::string>	index(void)					const;
		bool						directory_listing(void)		const;
		std::string					get_directory_file(void)	const;
		std::string					cgi(void)					const;
		bool						upload_allowed(void)		const;
		std::string					get_upload_path(void)		const;

};

# endif
