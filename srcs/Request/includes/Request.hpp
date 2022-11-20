#ifndef REQUEST_HPP
# define REQUEST_HPP

# define BUFFER_SIZE 1024

# include "Utils.hpp"

# include <iostream>
# include <cstring>
# include <sys/socket.h>
# include <cstdio>

// Reference : https://www.rfc-editor.org/rfc/rfc2616#section-5

class	Request
{
	public:

		Request(void);
		~Request(void);

		string				request;
		string				method;
		string				uri;
		string				http_version;
		string				host;
		pair<string, int>	request_address;

		string 				boundary;
		vector<string>		content;
		vector<string>		body_content;
		vector<string>		content_type;
		vector<string> 		file_name;


		int	get(int);
		int	interpret(void);

	private:

		int		get_request_line(string &);
		int		get_method(string &, size_t &);
		int 	get_request_uri(string &, size_t &);
		int		get_http_version(string &, size_t &);
		int		get_host(void);

		int		get_boundary_content(void);
		int		get_body_content(size_t i);
		int 	get_content_type(size_t i);
		int 	get_file_name(size_t i);
		int 	get_content(void);

		int		set_content(void);
		int		host_to_address(void);

		void	reset(void);

};

#endif
