/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserver.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 21:43:53 by cmariot           #+#    #+#             */
/*   Updated: 2022/10/12 15:02:49 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Webserver.hpp"

Webserver::Webserver(void)
{
	std::cout << "Server creation" << std::endl;
};

Webserver::~Webserver(void)
{
	std::cout << "Server destruction" << std::endl;
};

int	Webserver::parse(int argc, const char *argv[])
{
	if (argc == 1)
	{
		// Default config
	}
	else if (argc == 2)
	{
		// Parse the file argv[1]
		std::ifstream	configuration_file;

		configuration_file.open(argv[1]);
		if (configuration_file.is_open() == false)
		{
			std::cerr << "Cannot open the file " << argv[1] << std::endl;
			return (1);
		}
		std::cout << "Let's parse " << argv[1] << std::endl;
		for (int i = 0 ; i < 5 ; ++i)
			this->server.push_back(Server());
		configuration_file.close();
	}
	else
		return (usage());
	std::cout << "Number of servers = " << this->server.size() << std::endl;	
	return (0);
};

int	Webserver::usage(void)
{
	std::cerr << RED_COLOR
		<< "Usage: ./webserv [Configuration file]"
		<< RESET_COLOR << std::endl;
	return (1);
};
