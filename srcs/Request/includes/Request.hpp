#ifndef REQUEST_HPP
# define REQUEST_HPP

# define BUFFER_SIZE 1024

# include "Utils.hpp"

# include <iostream>
# include <cstring>
# include <sys/socket.h>
# include <cstdio>

// Reference : https://www.rfc-editor.org/rfc/rfc2616#section-5

using	namespace std;

class	Request
{


	public:

		Request(void);
		~Request(void);

		std::string			request;
		std::string			method;
		std::string			uri;
		std::string			http_version;
		std::string			host;
		pair<string, int>	request_address;
		std::string			content_type;
		std::string 		file_name;
		std::string			content;

		int	get(int);
		int	interpret(void);

	private:

		int		get_request_line(std::string &);
		int		get_method(std::string &, size_t &);
		int 	get_request_uri(std::string &, size_t &);
		int		get_http_version(std::string &, size_t &);
		int		get_host(void);
		int 	get_content(void);
		int     set_content(void);
		int		host_to_address(void);

};

#endif
