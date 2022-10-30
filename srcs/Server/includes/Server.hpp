/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:44:38 by cmariot           #+#    #+#             */
/*   Updated: 2022/10/30 14:34:41 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <cstdio>

class	Directive_error_page
{

	public:

		Directive_error_page() :
			_error(0),
			_change_response(false),
			_specified_response(false),
			_redirection(0),
			_path("")
		{
			return ;
		};

		~Directive_error_page()
		{
			return ;
		};

		void	set_error(int error)
		{
			_error = error;
		}

		void	set_change_response(bool change)
		{
			_change_response = change;
		}

		void	set_specified_response(bool specified)
		{
			_specified_response = specified;
		}

		void	set_redirection(int redirection)
		{
			_redirection = redirection;
		}

		void	set_path(std::string path)
		{
			_path = path;
		}

		int			get_error(void) const
		{
			return (_error);
		}

		bool		get_change_response(void) const
		{
			return (_change_response);
		}

		bool		get_specified_response(void) const
		{
			return (_specified_response);
		}

		int			get_redirection(void) const
		{
			return (_redirection);
		}

		std::string	get_path(void) const
		{
			return (_path);
		}

	private:

		int				_error;
		bool			_change_response;
		bool			_specified_response;
		int				_redirection;
		std::string		_path;

};

class	Server
{

	public:

		std::pair<std::string, int>			address;		// Pair Host:Port
		std::string							server_name;
		double								client_max_body_size;
		std::vector<Directive_error_page>	error_pages;
		std::vector<void *>					locations;

		int									server_socket;
		struct sockaddr_in					server_address;

		Server();
		~Server();

		int			set_server_arguments(std::vector<std::string> &);

		int			create_server_socket(void);
		int			set_server_socket_options(void);
		int			bind_server_address(void);
		int			listen_for_clients(void) const;

	private :

		int			parse_listen_directive(std::vector<std::string> &, size_t &);
		int			parse_server_name_directive(std::vector<std::string> &, size_t &);
		int			parse_error_page_directive(std::vector<std::string> &, size_t &);
		int			parse_client_max_body_size_directive(std::vector<std::string> &, size_t &);
		int			parse_location_context(std::vector<std::string> &, size_t &);

		bool		invalid_directive_len(std::vector<std::string> &, size_t, std::string, size_t, size_t);
		int			set_ip_and_port(std::vector<std::string> &, size_t &);
		std::string	set_ip(std::string);
		int			set_client_max_body_size(std::string & str);

		int			error(const char *error) const;
		int			error(const char *error, const char *complement) const;
};

#endif
