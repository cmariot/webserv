/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserver.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 21:43:53 by cmariot           #+#    #+#             */
/*   Updated: 2022/10/13 18:03:24 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Webserver.hpp"

// Default constructor
Webserver::Webserver(void)
{
	return ;
};

// Default destructor
Webserver::~Webserver(void)
{
	return ;
};

// Check the number of arguments,
// if the file can be opened and
// store the file content in a string vector.
// Next -> Get the server blocks
int	Webserver::parse(int argc, const char *argv[])
{
	std::fstream				configuration_file;
	std::string					line;
	std::vector<std::string>	string_vector;

	if (argc != 2)
		return (usage());
	else
	{
		configuration_file.open(argv[1]);
		if (configuration_file.is_open() == false)
			return (error("Cannot open the file ", argv[1]));
		while (getline(configuration_file, line))
			string_vector.push_back(line);
		configuration_file.close();
		for (size_t i = 0 ; i < string_vector.size() ; ++i)
			std::cout << string_vector[i] << std::endl;
	}
	return (0);
};

// Display the webserv usage
int	Webserver::usage(void) const
{
	const char	*red_color	= "\033[1m\033[31m";
	const char	*reset		= "\033[0m";

	std::cerr << red_color
		<< "Usage: ./webserv [configuration_file]"
		<< reset << std::endl;
	return (1);
};

// Display an error and an optional complement
int	Webserver::error(const char *error, const char *complement) const
{
	const char	*red_color	= "\033[1m\033[31m";
	const char	*reset		= "\033[0m";

	std::cerr << red_color << "Error: " << error;
	if (complement != NULL)
		std::cerr << complement;
	std::cerr << reset << std::endl;
	return (1);
};
