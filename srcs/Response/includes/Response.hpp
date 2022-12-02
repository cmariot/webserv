#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include "Utils.hpp"
# include "Request.hpp"
# include "Server.hpp"

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

		// Update
		int									get_location(void);

		void								get_method(void);
		void								post_method(void);
		void								delete_method(void);

		// Create
		bool								uri_too_long(void) const;
		bool								header_too_large(void) const;
		bool								method_not_implemented(void) const;
		bool 								method_not_allowed(void) const;
		bool								expect_100_continue(void);
		bool								has_content(void) const;
		bool 						  		content_too_large(void) const;
		bool								request_block_not_ok(void) const;

		// Get
		bool								redirection(void) const;
		void								generate_redirection(void);
		bool								construct_path(void);
		bool								is_forbidden(void) const;
		bool								is_a_directory(void) const;
		bool								directory_file_set(void) const;
		void								generate_directory_file(void);
		bool								directory_listing_set(void) const;
		void								generate_directory_list(void);
		bool								use_cgi(void) const;
		void								generate_cgi_response(void);
		void								generate_file_response(void);

		// Error
		void								generate_error_page(const int &);
		void								generate_100_continue(void);

};

#endif
