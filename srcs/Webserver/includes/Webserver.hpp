/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserver.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 21:38:22 by cmariot           #+#    #+#             */
/*   Updated: 2022/10/18 18:48:17 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERVER_HPP
# define WEBSERVER_HPP

# include <fstream>
# include <vector>
# include <string>
# include <cstring>
# include <istream>
# include <iostream>
# include <sstream>

class Webserver
{

	private:

		std::vector<void *>		virtual_server;

	public:

		// Default constructor
		Webserver(void);

		// Destructor
		~Webserver(void);

		// Parse the main's arguments
		int		parse(int argc, const char *argv[]);

	private:

		// Display an error explaining the Webserv usage
		int		usage(void) const;

		// Display an error with the error message (complement can be set to NULL)
		int		error(const char *error, const char *complement) const;

		int		parse_configuration_file(std::vector<std::string> &) const;
		int		remove_commentaries(std::vector<std::string> &) const;
		int		replace_blank_characters(std::vector<std::string> & string_vector) const;
		int		split_strings(std::vector<std::string> &, std::vector<std::string>	&) const;
		int		separate_braces(std::vector<std::string> &) const;

};

#endif
