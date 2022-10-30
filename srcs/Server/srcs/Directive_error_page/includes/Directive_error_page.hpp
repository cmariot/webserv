/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Directive_error_page.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 14:40:55 by cmariot           #+#    #+#             */
/*   Updated: 2022/10/30 15:55:08 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIRECTIVE_ERROR_PAGE_HPP
# define DIRECTIVE_ERROR_PAGE_HPP

#include <string>

class	Directive_error_page
{

	public:

		Directive_error_page(int &, bool &, bool &, int &, std::string &);
		~Directive_error_page();

		void			set_error(int error);
		void			set_change_response(bool change);
		void			set_specified_response(bool specified);
		void			set_redirection(int redirection);
		void			set_path(std::string path);

		int				get_error(void) const;
		bool			get_change_response(void) const;
		bool			get_specified_response(void) const;
		int				get_redirection(void) const;
		std::string		get_path(void) const;

	private:

		int				_error;
		bool			_change_response;
		bool			_specified_response;
		int				_redirection;
		std::string		_path;

};

#endif
