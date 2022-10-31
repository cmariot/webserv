/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:21:52 by cmariot           #+#    #+#             */
/*   Updated: 2022/10/31 19:30:53 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

int	main(int argc, const char *argv[])
{
	Webserver	webserv;

	if (webserv.parse(argc, argv))
		return (0);
	if (webserv.launch())
		return (0);
	return (0);
}
