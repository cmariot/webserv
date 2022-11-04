#ifndef REQUEST_HPP
# define REQUEST_HPP

# define BUFFER_SIZE 1024

# include "Utils.hpp"

# include <iostream>
# include <cstring>
# include <sys/socket.h>
# include <cstdio>

class	Request
{

	public:

		Request(void);
		~Request(void);

		std::string		request;

		int	get_client_request(int);

};

#endif
