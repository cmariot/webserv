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

		std::string		request;

		std::string		_method;
		std::string		_request_uri;
		std::string		_http_version;
		std::string		_host;

		std::pair<std::string, int>		_request_address;

		int	get_client_request(int);
		int	interpret(void);

	private:

		int	get_request_line(std::string &);
		int	get_method(std::string &, size_t &);
		int get_request_uri(std::string &, size_t &);
		int	get_http_version(std::string &, size_t &);
		int	get_host(void);
		int	host_to_address(void);

};

#endif
