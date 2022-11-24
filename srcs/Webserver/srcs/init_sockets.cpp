#include "Webserver.hpp"

// Ouvrir un epoll_socket avec epoll_create1, c'est le socket principal
int		Webserver::create_epoll_descriptor(void)
{
	const int	flags = 0;

	print(INFO, "Opening the epoll_socket.");
	epoll_socket = epoll_create1(flags);
	if (epoll_socket == -1)
		return (error("epoll_create1"));
	return (0);
};

// Ouvrir un socket pour chaque serveur
int		Webserver::open_server_socket(Server & server)
{
	const int	socket_family	= AF_INET;						// IPv4 Internet protocols
	const int	socket_type		= SOCK_STREAM | SOCK_NONBLOCK;	// TCP
	const int	protocol		= IPPROTO_TCP;					// IP

	print(INFO, "Opening a server_socket.");
	server.socket = socket(socket_family, socket_type, protocol);
	if (server.socket == -1)
		return (error("socket server"));
	return (0);
};

// Assigner un type, un host et un port a l'addresse de ce socket
int		Webserver::bind_server_address(Server & server)
{
	const int		socket_family	= AF_INET;						// IPv4 Internet protocols
	const int		server_port		= server.get_port();			// Listening port
	const char		*server_host	= server.get_host().c_str();	// Listening IP address

	bzero(&server.address, sizeof(struct sockaddr_in));
	server.address.sin_family = socket_family;
	server.address.sin_port = htons(server_port);
	server.address.sin_addr.s_addr = inet_addr(server_host);

	const struct sockaddr	*addr	= (const struct	sockaddr *)&server.address;
	socklen_t				addrlen = sizeof(server.address);

	print(INFO, "Binding the server_socket with an address.");
	if (bind(server.socket, addr, addrlen) == -1)
		return (error("bind server"));
	return (0);
};

// do nonblocking I/O on sockets by setting the O_NONBLOCK flag on a socket.
int		Webserver::set_non_blocking(Server & server)
{
	print(INFO, "Set the non-blocking flag on the server_socket.");
	int	flags = fcntl(server.socket, F_GETFL, 0);
	if (flags == -1
			|| fcntl(server.socket, F_SETFL, flags | O_NONBLOCK) == -1)
		return (error("fcntl server"));
	return (0);
};

// tells the socket that new connections shall be accepted
int		Webserver::listen_server(Server & server)
{
	const int	backlog = 100;

	print(INFO, "Tells the socket that new connections shall be accepted.");
	if (listen(server.socket, backlog) == -1)
		return (error("listen server"));
	return (0);
};

// Add the socket server to the epoll interest_list
int		Webserver::add_to_epoll_interest_list(Server & server)
{
	print(INFO, "Add the server_socket on the epoll interest_list.");
	bzero(&server.event, sizeof(struct epoll_event));
	server.event.data.fd = server.socket;
	server.event.events = EPOLLIN | EPOLLOUT | EPOLLET | EPOLLRDHUP;
	if (epoll_ctl(epoll_socket, EPOLL_CTL_ADD, server.socket, &(server.event)) == -1)
		return (error("epoll_ctl ADD server"));
	return (0);
};

int		Webserver::init_sockets(void)
{
	if (create_epoll_descriptor())
		return (1);
	for (size_t i = 0 ; i < nb_of_servers ; ++i)
	{
		if (open_server_socket(server[i]))
			return (1);
		else if (bind_server_address(server[i]))
			return (1);
		else if (set_non_blocking(server[i]))
			return (1);
		else if (listen_server(server[i]))
			return (1);
		else if (add_to_epoll_interest_list(server[i]))
			return (1);
	}
	return (0);
};
