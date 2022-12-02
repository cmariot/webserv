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
		void								get(void);
		void								post(void);
		void								delaite(void);
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

		void								get(void);
		void								post(void);
		void								delet(void);

		// Create
		bool								uri_too_long(void) const;
		bool								header_too_large(void) const;
		bool								method_not_implemented(void) const;
		bool 								method_not_allowed(void) const;
		bool								expect_100_continue(void);
		bool								has_content(void) const;
		bool 						  		content_too_large(void) const;
		bool								is_forbidden(void) const;
		bool								request_block_not_ok(void) const;

		// Error
		void								generate_error_page(const int &);
		void								generate_100_continue(void);

};

#endif
