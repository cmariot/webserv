#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "Server.hpp"
# include "Request.hpp"
# include "Response.hpp"
# include "Utils.hpp"

class	Client
{

	public:

		Client(const int &, const Server &);
		~Client(void);

	private:

		int			_socket;
		Server		_server;
		Request		_request;
		Response	_response;

};

#endif
