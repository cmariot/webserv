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

		void	update(Request &, Server &, char * const *);
		void	create(void);

		const std::string	& get_response(void) const;

	private:

		int									_status_code;
		const std::map<int, std::string>	_status_code_map;

		Request								_request;
		Server								_server;
		char * const *						_env;

		std::string							_response;

};

#endif
