#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>
# include <string>
# include <vector>

// error.cpp
int		error(std::string);
int		error(std::string, std::string);

// invalid_directive_len.cpp
bool	invalid_directive_len(std::vector<std::string> &, size_t, std::string, size_t, size_t);
bool	no_semicolon(std::vector<std::string> &, size_t &);

#endif
