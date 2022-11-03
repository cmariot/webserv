#include "Webserver.hpp"

int		Webserver::separate_semicolon(std::vector<std::string>	& tokens_vector) const
{
	std::vector<std::string>	tmp_vector;
	std::string					previous_word;
	size_t						begin;
	size_t						len;
	const size_t				vector_size = tokens_vector.size();

	try
	{
		for (size_t i = 0 ; i < vector_size ; ++i)
		{
			begin = 0;
			len = 0;

			if (tokens_vector[i].find(";") != std::string::npos)
			{
				for (size_t j = 0 ; j < tokens_vector[i].size() ; ++j)
				{
					if (tokens_vector[i][j] == ';')
					{
						if (len == 0)
							tmp_vector.push_back(";");
						else
						{
							previous_word = tokens_vector[i].substr(begin, len);
							tmp_vector.push_back(previous_word);
							tmp_vector.push_back(";");
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
	}
	catch (const std::bad_alloc & exception)
	{
		return (error(exception.what(), "(separate_semicolon)"));
	}
	catch (const std::out_of_range & exception)
	{
		return (error(exception.what(), "(out_of_range exception in separate_semicolon)"));
	}
	return (0);
};
