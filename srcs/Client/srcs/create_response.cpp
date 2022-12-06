#include "Client.hpp"

int	Client::get_server(const std::vector<Server> & servers)
{
	for (size_t i = 0 ; i < servers.size() ; ++i)
	{
		if ((servers[i].get_server_names().count(_request.get_host()) == 1
				&& servers[i].get_address().second == _request.get_port())
			|| servers[i].get_address() == _request.get_address())
		{
			set_server(servers[i]);
			return (0);
		}
	}
	set_server(Server());
	return (error("A client has not any corresponding server."));
};

int	Client::create_response(const std::vector<Server> & servers, char * const *env)
{
	get_server(servers);
	_response.update(_request, _server, env);
	_response.main_create();
	_request.clear();
	print(INFO, "Response :");
	std::cout << _response.get_response() << std::endl;
	return (0);
};
