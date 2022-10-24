/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:44:38 by cmariot           #+#    #+#             */
/*   Updated: 2022/10/24 17:16:15 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include <iostream>
#include <vector>
#include <string>

class	Server
{

	private:

		std::string				ip;
		int						port;
		std::string				server_name;
		std::vector<void *>		error_pages;
		size_t					max_body_size;
		std::vector<void *>		locations;

	public:

		Server();

		~Server();

		int	set_server_arguments(std::vector<std::string> &);

};

#endif
