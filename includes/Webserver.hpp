/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserver.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 21:38:22 by cmariot           #+#    #+#             */
/*   Updated: 2022/10/12 14:32:06 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERVER_HPP
# define WEBSERVER_HPP

# include <iostream>
# include <fstream>
# include <vector>

# define RED_COLOR		"\033[1m\033[31m"
# define RESET_COLOR	"\033[0m"

class Server
{
	public:

		int		ID;

		Server()
		{
			std::cout << "New server" << std::endl;
			ID = 42;
		};

		~Server()
		{
			std::cout << "Server down" << std::endl;
		};

	private:

};

class Webserver
{

	private:


	public:

		std::vector<Server>		server;

		// Default constructor
		Webserver(void);

		// Destructor
		~Webserver(void);

		// Copy assignation
		Webserver(const Webserver &);

		// Operator =
		Webserver & operator = (const Webserver &);

		// Parse the configuration file given as argument
		int		parse(int argc, const char *argv[]);

	private:

		// Display an error explaining the Webserv usage
		int		usage(void);
};

#endif
