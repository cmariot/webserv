#include "Server.hpp"

// error_page 404             /404.html;
// error_page 500 502 503 504 /50x.html;
// error_page 404 =200 /empty.gif;
// error_page 404 = /404.php;

// 1- Parsing du path
// 2- parsing (s'il y en a) du code response
// 3- Parsing du ou des codes d'erreurs a ajouter dans un vecteur
// Ajout de chaque triplet au vecteur error_page du serveur
int	Server::parse_error_page_directive(std::vector<std::string> & token_vector, size_t & i)
{
	int			code;
	bool		change_response = false;
	bool		specified_response = false;
	int			response = 0;
	std::string	path;
	size_t		j = i;

	if (invalid_directive_len(token_vector, i + 1, ";", 4, token_vector.size()))
		return (error("Syntax error : invalid error_page directive."));
	while (token_vector[j + 1] != ";")
		++j;
	path = token_vector[j--];
	if (token_vector[j].find("=") != std::string::npos)
	{
		if (token_vector[j][0] != '=')
			return (error("Syntax error : invalid error_page directive (=response)."));
		change_response = true;
		if (token_vector[j].size() > 1)
		{
			size_t k = 1;
			size_t	result_len = 0;

			specified_response = true;
			while (k < token_vector[j].size())
			{
				if (token_vector[j][k] < '0' || token_vector[j][k] > '9')
					return (error("Syntax error : invalid error_page directive (=response)."));
				response = response * 10 + token_vector[j][k++] - '0';
				if (++result_len > 3)
					return (error("Syntax error : invalid error_page directive (=response)."));
			}
		}
		--j;
	}
	while (i != j)
	{
		++i;
		Directive_error_page	directive;

		code = 0;
		size_t k = 0;
		size_t	result_len = 0;

		while (k < token_vector[i].size())
		{
			if (token_vector[i][k] < '0' || token_vector[i][k] > '9')
				return (error("Syntax error : invalid error_page directive (=response)."));
			code = code * 10 + token_vector[i][k++] - '0';
			if (++result_len > 3)
				return (error("Syntax error : invalid error_page directive (code)."));
		}
		directive.set_error(code);
		directive.set_change_response(change_response);
		directive.set_specified_response(specified_response);
		directive.set_redirection(response);
		directive.set_path(path);
		error_pages.push_back(directive);
	}
	while (token_vector[i] != ";")
		++i;

	for (size_t j = 0 ; j < error_pages.size() ; ++j)
	{
		std::cout << "\terror_pages\t\t" << error_pages[j].get_error() << " ";
		if (error_pages[j].get_change_response() == true)
		{
			std::cout << "=";
			if (error_pages[j].get_specified_response())
				std::cout << error_pages[j].get_redirection() << " ";
			else
				std::cout << " ";
		}
		std::cout << error_pages[j].get_path() << ";" << std::endl;

	}
	return (0);
};
