#include "Request.hpp"

// On stocke dans une string la requete envoyee sur le fd avec recv
// Exemple de requete :
//
// GET / HTTP/1.1
// Host: 127.0.0.1:8080
// User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux aarch64; rv:106.0) Gecko/20100101 Firefox/106.0
// Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8
// Accept-Language: en-US,en;q=0.5
// Accept-Encoding: gzip, deflate, br
// DNT: 1
// Connection: keep-alive
// Upgrade-Insecure-Requests: 1
// Sec-Fetch-Dest: document
// Sec-Fetch-Mode: navigate
// Sec-Fetch-Site: none
// Sec-Fetch-User: ?1

int	Request::get(int fd)
{
	(void)fd;
//	char	buffer[BUFFER_SIZE + 1];
//	int		recv_return = BUFFER_SIZE + 1;
//
//	print(INFO, "Getting the client's request");
//	request.clear();
//	// Interdit, 1 seul appel recv par event
//	while (true)
//	{
//		bzero(buffer, recv_return);
//		recv_return = recv(fd, buffer, BUFFER_SIZE, 0);
//		if (recv_return == -1)
//		{
//			perror("recv");
//			return (error("recv request failed"));
//		}
//		request += buffer;
//		if (recv_return < BUFFER_SIZE)
//			break ;
//	}
//	interpret();
	return (0);
};
