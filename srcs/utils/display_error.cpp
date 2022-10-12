/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_error.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:23:19 by cmariot           #+#    #+#             */
/*   Updated: 2022/10/11 22:12:51 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

int	display_error(std::string error_message)
{
	std::cerr << RED_COLOR
		<< "Error: " << error_message
		<< RESET_COLOR << std::endl;
	return (1);
}
