#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "Server.hpp"
# include "Request.hpp"
# include "Response.hpp"
# include "Utils.hpp"

class	Client
{
	private:

		int			_socket;
		Server		_server;
		Request		_request;
		Response	_response;

	public:

		Client(const int &);
		~Client(void);

		int							add_to_request(char *);

		bool						request_is_ready(void);

		int							create_response(const std::vector<Server> &, char * const *);
		int							get_server(const std::vector<Server> &);

		const char *				get_response(void) const;
		size_t						get_response_size(void) const;
		std::string					get_hostname(void) const;
		int							get_port(void) const;
		std::pair<std::string, int>	get_address(void) const;

		void						set_server(const Server &);

};

#endif
