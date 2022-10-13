/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserver.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 21:38:22 by cmariot           #+#    #+#             */
/*   Updated: 2022/10/13 18:18:04 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERVER_HPP
# define WEBSERVER_HPP

# include <iostream>
# include <fstream>
# include <vector>
# include <string>

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

};

#endif
