#ifndef ERROR_PAGE_HPP
# define ERROR_PAGE_HPP

#include <string>

/* Classe pour stocker la directive 'error_page' du fichier de configuration.
 * Construit dans les blocs 'location' a partir de la forme :
 * error_page	code ... [=[response]] uri;
 */

class	Error_page
{

	public:

		Error_page(int &, bool &, bool &, int &, std::string &);
		~Error_page(void);

		int				get_code(void) const;
		bool			change_response(void) const;
		bool			specified_response(void) const;
		int				get_changed_code(void) const;
		std::string		get_path(void) const;

	private:

		int				_code;					// The error code to treat
		bool			_change_response;		// If we need to create a redirection
		bool			_specified_response;	// If we know the redirection code
		int				_changed_response;		// If _specified_response is true change the response with this code
		std::string		_path;					// The path of the file

};

#endif
