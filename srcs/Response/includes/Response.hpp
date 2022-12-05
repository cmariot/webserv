#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include "Utils.hpp"
# include "Request.hpp"
# include "Server.hpp"

# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <unistd.h>
# include <sstream>
# include <iterator>

# define BUFFER_SIZE 4096

class Response
{

	public:

		Response(void);
		~Response(void);

		void								update(Request &, Server &, char * const *);
		void								main_create(void);
		const std::string &					get_response(void) const;

	private:

		int									_status_code;
		const std::map<int, std::string>	_status_code_map;

		Request								_request;
		Server								_server;
		Location							_location;
		bool								_no_location;
		char * const *						_env;

		std::string							_header;
		std::string							_body;
		std::string							_response;

		std::string							_path;
		

		// Update
		int									get_location(void);

		// Create
		bool								uri_too_long(void) const;
		bool								header_too_large(void) const;
		bool								method_not_implemented(void) const;
		bool 								method_not_allowed(void) const;
		bool								expect_100_continue(void);
		bool								has_content(void) const;
		bool 						  		content_too_large(void) const;
		bool								request_block_not_ok(void) const;

		// Methods
		void								get_method(void);
		void								post_method(void);
		void								delete_method(void);

		// Get
		bool								redirection(void) const;
		bool								file_not_found(void);
		bool								is_forbidden(void) const;
		bool								is_a_directory(void) const;
		bool								directory_file_set(void) const;
		bool								directory_listing_set(void) const;
		int									directory_listing_body(void);
		const std::string 					add_dot_link(void);
		const std::string 					add_double_dot_link(void);
		const std::string 					add_other_link(char d_name[256]);
		bool								use_cgi(void) const;

		// Generate
		void								generate_error_page(const int &);
		void								generate_100_continue(void);
		void								generate_redirection(void);
		void								generate_directory_file(void);
		void								generate_directory_list(void);
		int									generate_cgi_response(void);
		void								generate_file_response(void);

};

#endif
