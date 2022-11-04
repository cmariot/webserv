#ifndef LOCATION_HPP
# define LOCATION_HPP

# include <iostream>
# include <vector>
# include <string>

# include "Utils.hpp"

class Location
{

	public:

		Location(std::string & uri);
		~Location(void);

		int				parse(std::vector<std::string> &);

	private:

		std::string		_uri;
		bool			_get_allowed;
		bool			_post_allowed;
		bool			_delete_allowed;
		bool			_redirection;
		size_t			_redirection_code;
		std::string		_redirection_path;
		std::string		_root;
		bool			_directory_listing;
		std::string		_directory_file;
		std::string		_cgi;
		bool			_upload;
		std::string		_upload_path;

		int				set_allow_methods(std::vector<std::string> &, size_t &);
		int				set_redirection(std::vector<std::string> &, size_t &);
		int				set_root(std::vector<std::string> &, size_t &);
		int				set_directory_listing(std::vector<std::string> &, size_t &);
		int				set_directory_file(std::vector<std::string> &, size_t &);
		int				set_cgi(std::vector<std::string> &, size_t &);
		int				set_upload(std::vector<std::string> &, size_t &);
		int				set_upload_path(std::vector<std::string> &, size_t &);

	public:

		std::string		get_uri(void)					const;
		bool			get_method_get(void)			const;
		bool			get_method_post(void)			const;
		bool			get_method_delete(void)			const;
		bool			get_redirection(void)			const;
		size_t			get_redirection_code(void)		const;
		std::string		get_redirection_path(void)		const;
		std::string		get_root(void)					const;
		bool			get_directory_listing(void)		const;
		std::string		get_directory_file(void)		const;
		std::string		get_cgi(void)					const;
		bool			get_upload(void)				const;
		std::string		get_upload_path(void)			const;

};

# endif
