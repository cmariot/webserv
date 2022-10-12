/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 22:29:01 by cmariot           #+#    #+#             */
/*   Updated: 2022/10/12 11:53:27 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# define RED_COLOR		"\033[1m\033[31m"
# define RESET_COLOR	"\033[0m"

# include <iostream>
# include <cstdio>
# include <cstdlib>
# include <cstring>
# include <unistd.h>

# include <sys/types.h>
# include <errno.h>
# include <netinet/in.h>
# include <sys/socket.h>
# include <arpa/inet.h>

#include "Webserver.hpp"

// srcs/utils
int	display_error(std::string error);

// srcs/sockets
int	create_socket(int *socket_fd);
int	bind_socket_and_address(int socket_fd, struct sockaddr_in *address);
int listen_socket(int socket_fd);
int accept_connexion(int socket_fd, struct sockaddr_in address, int *accepted_socket);

#endif
