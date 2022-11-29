#include "Client.hpp"

int	Client::get_server(const std::vector<Server> & servers)
{
	for (size_t i = 0 ; i < servers.size() ; ++i)
	{
		if ((servers[i].get_server_names().count(_request.host) == 1
				&& servers[i].get_address().second == _request.request_address.second)
			|| servers[i].get_address() == _request.request_address)
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
	if (get_server(servers))
		_response.set_status_code(404);

	_response.update(_request, _server, env);
	_response.create();
	_request.request.clear();

	return (0);
};
