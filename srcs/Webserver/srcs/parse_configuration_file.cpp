#include "Webserver.hpp"

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
	std::vector<std::string>	tokens_vector;

	if (remove_commentaries(string_vector))
		return (1);
	if (replace_blank_characters(string_vector))
		return (1);
	if (split_strings(string_vector, tokens_vector))
		return (1);
	if (separate_braces(tokens_vector))
		return (1);
	if (separate_semicolon(tokens_vector))
		return (1);
	for (size_t i = 0 ; i < tokens_vector.size() ; ++i)
		std::cout << "TOKENS_VECTOR[" << i << "] = " << tokens_vector[i] << std::endl;
	if (parse_server(tokens_vector))
		return (1);
	return (0);
};
