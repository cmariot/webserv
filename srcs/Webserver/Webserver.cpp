/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserver.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 21:43:53 by cmariot           #+#    #+#             */
/*   Updated: 2022/10/17 16:39:02 by cmariot          ###   ########.fr       */
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

#include <sstream>

/* nginx consists of modules which are controlled by directives specified in the configuration file.
 *
 * Directives are divided into simple directives and block directives.
 * - A simple directive consists of the name and parameters separated by spaces and ends with a semicolon (;).
 * - A block directive has the same structure as a simple directive,
 *   but instead of the semicolon it ends with a set of additional instructions surrounded by braces ({ and }).
 *
 * If a block directive can have other directives inside braces, it is called a context (examples: events, http, server, and location).
 * Directives placed in the configuration file outside of any contexts are considered to be in the main context.
 * The events and http directives reside in the main context, server in http, and location in server.
 * The rest of a line after the # sign is considered a comment
 */

int		Webserver::parse_configuration_file(std::vector<std::string> & string_vector)
{
	const size_t	vector_size = string_vector.size();

	// Remove the commentaries from the vector
	for (size_t i = 0 ; i < vector_size ; ++i)
	{
		size_t comment_pos = string_vector[i].find("#");
		if (comment_pos != std::string::npos &&
				(comment_pos == 0 || isblank(string_vector[i][comment_pos - 1])))
			string_vector[i] = string_vector[i].substr(0, comment_pos);
	}
	// Replace all the blank characters by spaces
	for (size_t i = 0 ; i < vector_size ; ++i)
		for (size_t j = 0 ; j < string_vector[i].size() ; ++j)
			if (isblank(string_vector[i][j]))
				string_vector[i][j] = ' ';

	// Split the strings with ' ', '{' and '}' as delimiters
	std::string					token;
	std::vector<std::string>	tokens_vector;

	for (size_t i = 0 ; i < vector_size ; ++i)
	{
		std::istringstream	iss(string_vector[i]);
		while (std::getline(iss, token, ' '))
		{
			if (token.empty() == false)
			{
				if (token.find("{") != std::string::npos
					|| token.find("}") != std::string::npos)
				{
					if (token == "{" || token == "}")
						tokens_vector.push_back(token);
					else
					{
						size_t	begin = 0;
						size_t	len = 0;

						for (size_t j = 0 ; j < token.size() ; ++j)
						{
							if (token[j] == '{' || token[j] == '}')
							{
								if (j != begin)
								{
									len = j;
									std::cout << "STR = " << token << " SUBSTR BEGIN = " << begin << "LEN = " << len << std::endl;
									tokens_vector.push_back(token.substr(begin, len));
								}
								if (token[j] == '{')
									tokens_vector.push_back("{");
								else if (token[j] == '}')
									tokens_vector.push_back("}");
								begin = j + 1;
							}
						}
					}
				}
				else
					tokens_vector.push_back(token);
			}
		}
	}

	for (size_t i = 0 ; i < tokens_vector.size() ; ++i)
	{
		if (tokens_vector[i] == "server")
		{
			std::cout << "SERVER !" << std::endl;
			
		}
		std::cout << "tokens_vector[" << i << "] = " << tokens_vector[i] << std::endl;
	}

	return (0);
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
			return (error("Cannot open the file", argv[1]));
		while (std::getline(configuration_file, line))
			string_vector.push_back(line);
		if (configuration_file.eof() == false)
		{
			configuration_file.close();
			return (error("while reading the file", argv[1]));
		}
		configuration_file.close();
		if (parse_configuration_file(string_vector))
			return (1);
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
		std::cerr << " " << complement;
	std::cerr << reset << std::endl;
	return (1);
};
