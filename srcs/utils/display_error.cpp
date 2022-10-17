/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_error.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 13:09:19 by cmariot           #+#    #+#             */
/*   Updated: 2022/10/08 13:33:13 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

# ifndef RED_COLOR
#  define RED_COLOR		"\033[1m\033[31m"
# endif

# ifndef RESET_COLOR
#  define RESET_COLOR	"\033[0m"
# endif

using namespace std;

int	display_error(string error_message)
{
	cerr << RED_COLOR << "Error: " << error_message << RESET_COLOR << endl;
	return (1);
}
