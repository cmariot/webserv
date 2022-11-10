#include "Server.hpp"

int get_error(int & code, std::vector<std::string> & token_vector, size_t & i)
{
	size_t	k = 0;
	size_t	result_len = 0;

	code = 0;
	while (k < token_vector[i].size())
	{
		if (token_vector[i][k] < '0' || token_vector[i][k] > '9' || ++result_len > 3)
			return (1);
		code = code * 10 + token_vector[i][k++] - '0';
	}
	return (0);
}

int	get_response(std::vector<std::string> & token_vector, size_t & j, bool & change_response, bool & specified_response, int & response)
{
	size_t	k = 1;
	size_t	result_len = 0;

	if (token_vector[j].find("=") != std::string::npos)
	{
		if (token_vector[j][0] != '=')
			return (1);
		change_response = true;
		if (token_vector[j].size() > 1)
		{
			specified_response = true;
			while (k < token_vector[j].size())
			{
				if (token_vector[j][k] < '0' || token_vector[j][k] > '9' || ++result_len > 3)
					return (1);
				response = response * 10 + token_vector[j][k++] - '0';
			}
		}
		--j;
	}
	return (0);
};

// error_page 404             /404.html;
// error_page 500 502 503 504 /50x.html;
// error_page 404 =200 /empty.gif;
// error_page 404 = /404.php;

// 1- Parsing du path
// 2- parsing (s'il y en a) du code response
// 3- Parsing du ou des codes d'erreurs a ajouter dans un vecteur
// Ajout de chaque triplet au vecteur error_page du serveur
int	Server::set_error_pages(std::vector<std::string> & token_vector, size_t & i)
{
	int			code;
	bool		change_response = false;
	bool		specified_response = false;
	int			response = 0;
	std::string	path;
	size_t		j = i;

	if (no_semicolon(token_vector, j))
		return (error("Syntax error : the error_page directive doesn't ends with the ';' character."));
	else if (invalid_directive_len(token_vector, i + 1, ";", 3, token_vector.size()))
		return (error("Syntax error : invalid error_page directive len."));
	path = token_vector[j--];
	if (get_response(token_vector, j, change_response, specified_response, response))
		return (error("Syntax error : invalid response code in the error_page directive."));
	while (i != j)
	{
		if (get_error(code, token_vector, ++i))
			return (error("Syntax error : invalid error code in the error_page directive."));
		Error_page	directive(code, change_response, specified_response, response, path);
		if (_error_pages.insert(std::pair<int, Error_page>(directive.get_code(), directive)).second == false)
			return (error("Syntax error : Multiple declarations for the same error code in the error_page directives."));
	}
	while (token_vector[i] != ";")
		++i;
	error_page_set = true;
	return (0);
};
