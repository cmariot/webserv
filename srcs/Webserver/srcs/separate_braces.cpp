// string init
// push_back
// substr

#include "Webserver.hpp"

// Cut the strings before and after each '{' or '}'
int		Webserver::separate_braces(std::vector<std::string>	& tokens_vector) const
{
	std::vector<std::string>	tmp_vector;
	std::string					previous_word;
	size_t						begin;
	size_t						len;

	for (size_t i = 0 ; i < tokens_vector.size() ; ++i)
	{
		begin = 0;
		len = 0;

		if (tokens_vector[i].find("{") != std::string::npos
			|| tokens_vector[i].find("}") != std::string::npos)
		{
			for (size_t j = 0 ; j < tokens_vector[i].size() ; ++j)
			{
				if (tokens_vector[i][j] == '{' || tokens_vector[i][j] == '}')
				{
					std::string		brace(1, tokens_vector[i][j]);

					if (len == 0)
						tmp_vector.push_back(brace);
					else
					{
						previous_word = tokens_vector[i].substr(begin, len);
						tmp_vector.push_back(previous_word);
						tmp_vector.push_back(brace);
					}
					begin = j + 1;
					len = 0;
				}
				else
				{
					++len;
					if (j + 1 >= tokens_vector[i].size())
					{
						std::string	final_word = tokens_vector[i].substr(begin, len);
						tmp_vector.push_back(final_word);
					}
				}
			}
		}
		else
			tmp_vector.push_back(tokens_vector[i]);
	}
	tokens_vector = tmp_vector;
	return (0);
};
