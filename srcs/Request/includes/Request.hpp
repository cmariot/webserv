#ifndef REQUEST_HPP
# define REQUEST_HPP

# include "Utils.hpp"

# include <iostream>
# include <cstring>
# include <cstdio>
# include <map>

// Reference : https://www.rfc-editor.org/rfc/rfc2616#section-5

# define CRLF		"\r\n"

class	Request
{
	public:

		Request(void);
		~Request(void);

		void								add_to_request(const char *, const ssize_t &);
		bool								is_ready(void);
		void								clear(void);
	
		const std::string					& get_request(void) const;
		const std::string					& get_request_line(void) const;
		const std::string					& get_method(void) const;
		const std::string					& get_uri(void) const;
		const std::string					& get_http_version(void) const;
		const std::string					& get_host(void) const;
		const int							& get_port(void) const;
		const std::pair<std::string, int>	& get_address(void) const;
		const std::multimap<string, string> & get_header(void) const;
		const bool							& has_body(void) const;

	private:

		std::string							_request;			// Full request
		std::string							_request_line;		// 1st line of the request
		std::string							_method;			// GET, POST, DELETE
		std::string							_uri;				// Location uri
		std::string							_http_version;		// HTTP/1.1
		std::multimap<string, string>		_header;			// Map key/value
		std::pair<std::string, int>			_address;			// Host:Port
		size_t								_header_size;		// Request_line + Header
		bool								_has_body;			// True if body in the request

		int									set_request_line(size_t &);
		int									set_method(size_t &);
		int 								set_uri(size_t &);
		int									set_http_version(size_t &);

		bool								header_in_this_request(size_t &);
		int									set_header(size_t &);
		int									set_server_address(void);

		bool								body_in_this_request(void);
		bool								set_body(void);
		bool								unchunk(void);

	public:

		string 				boundary;
		vector<string>		content;
		vector<string>		body_content;
		vector<string>		content_type;
		vector<string> 		file_name;

		int					get_boundary_content(void);
		int					get_body_content(size_t i);
		int 				get_content_type(size_t i);
		int 				get_file_name(size_t i);
		int 				get_content(void);

		int					set_content(void);

		void				reset(void);

};

#endif
