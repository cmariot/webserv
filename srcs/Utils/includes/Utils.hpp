#ifndef UTILS_HPP
# define UTILS_HPP

# define INFO 0

# include <iostream>
# include <string>
# include <vector>

// error.cpp
int			error(std::string);
int			error(std::string, std::string);

// invalid_directive_len.cpp
bool		invalid_directive_len(std::vector<std::string> &, size_t, std::string, size_t, size_t);
bool		no_semicolon(std::vector<std::string> &, size_t &);

// set_ip_and_port.hpp
size_t		ft_atoi(std::string str);
size_t		set_port(std::string port);
std::string	set_ip(std::string ip);

// print.cpp
void		print(int, const char *);
void		print(int code, const char *, const char *);

std::string	itostring(int);

#endif
