#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>
# include <string>
# include <vector>

bool	invalid_directive_len(std::vector<std::string> &, size_t, std::string, size_t, size_t);
bool	no_semicolon(std::vector<std::string> &, size_t &);

int		error(std::string error);
int		error(std::string error, std::string complement);

#endif
