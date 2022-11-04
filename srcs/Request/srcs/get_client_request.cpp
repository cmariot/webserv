#include "Request.hpp"

int	Request::get_client_request(int fd)
{
	char			buffer[BUFFER_SIZE + 1];
	int				recv_return = BUFFER_SIZE + 1;

	request = std::string();
	while (true)
	{
		bzero(buffer, recv_return);
		recv_return = recv(fd, buffer, BUFFER_SIZE, 0);
		if (recv_return == -1)
		{
			perror("recv");
			return (error("recv request failed"));
		}
		request += buffer;
		if (recv_return < BUFFER_SIZE)
			break ;
	}
	return (0);
};
