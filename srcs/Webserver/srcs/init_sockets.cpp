#include "Webserver.hpp"

// Ouvrir un epoll_socket avec epoll_create1, c'est le socket principal
int		Webserver::create_epoll_descriptor(void)
{
	int	flags = 0;

	print(INFO, "Opening the epoll_socket.");
	epoll_socket = epoll_create1(flags);
	if (epoll_socket == -1)
		return (error(strerror(errno)));
	return (0);
};

// Ouvrir un socket pour chaque serveur
int		Webserver::open_server_socket(Server & server)
{
	int	socket_family	= AF_INET;						// IPv4 Internet protocols
	int	socket_type		= SOCK_STREAM | SOCK_NONBLOCK;	// TCP + NON-BLOCKING
	int	protocol		= IPPROTO_TCP;					// IP
	int	opt				= 1;

	print(INFO, "Opening a server_socket.");
	server.socket = socket(socket_family, socket_type, protocol);
	if (server.socket == -1)
		return (error(strerror(errno)));
	if (setsockopt(server.socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(int)) == -1)
		return (error(strerror(errno)));
	return (0);
};

// Assigner un type, un host et un port a l'addresse de ce socket
int		Webserver::bind_server_address(Server & server)
{
	int			socket_family	= AF_INET;						// IPv4 Internet protocols
	int			server_port		= server.get_port();			// Listening port
	const char	*server_host	= server.get_host().c_str();	// Listening IP address

	bzero(&server.address, sizeof(struct sockaddr_in));
	server.address.sin_family = socket_family;
	server.address.sin_port = htons(server_port);
	server.address.sin_addr.s_addr = inet_addr(server_host);		// A CHANGER : MODIF SUJET

	struct sockaddr	*addr	= (struct sockaddr *)&server.address;
	socklen_t		addrlen	= sizeof(server.address);

	print(INFO, "Binding the server_socket with an address.");
	if (bind(server.socket, addr, addrlen) == -1)
		return (error(strerror(errno)));
	return (0);
};

// do nonblocking I/O on sockets by setting the O_NONBLOCK flag on a socket.
int		Webserver::set_non_blocking(Server & server)
{
	print(INFO, "Set the non-blocking flag on the server_socket.");
	int	flags = fcntl(server.socket, F_GETFL, 0);
	if (flags == -1
			|| fcntl(server.socket, F_SETFL, flags | O_NONBLOCK) == -1)
		return (error(strerror(errno)));
	return (0);
};

// tells the socket that new connections shall be accepted
int		Webserver::listen_server(Server & server)
{
	const int	backlog = 100;

	print(INFO, "Tells the socket that new connections shall be accepted.");
	if (listen(server.socket, backlog) == -1)
		return (error(strerror(errno)));
	return (0);
};

// Add the socket server to the epoll interest_list
int		Webserver::add_to_epoll_interest_list(Server & server)
{
	struct epoll_event	new_event;

	print(INFO, "Add the server_socket on the epoll interest_list.");
	bzero(&new_event, sizeof(struct epoll_event));
    new_event.events = EPOLLIN | EPOLLOUT;
	new_event.data.fd = server.socket;
	if (epoll_ctl(epoll_socket, EPOLL_CTL_ADD, server.socket, &new_event) == -1)
		return (error(strerror(errno)));
	return (0);
};

int		Webserver::init_sockets(void)
{
	if (create_epoll_descriptor())
		return (1);
	for (size_t i = 0 ; i < nb_of_servers ; ++i)
	{
		if (open_server_socket(servers[i]))
			return (1);
		else if (bind_server_address(servers[i]))
			return (1);
		else if (set_non_blocking(servers[i]))
			return (1);
		else if (listen_server(servers[i]))
			return (1);
		else if (add_to_epoll_interest_list(servers[i]))
			return (1);
	}
	return (0);
};
