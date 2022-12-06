#ifndef UTILS_HPP
# define UTILS_HPP

# define INFO 0
# define ERR 1

# include <iostream>
# include <string>
# include <vector>
# include <map>
# include <set>
# include <sys/stat.h>
# include <sys/types.h>
# include <cstring>
# include <sstream>

using std::map;
using std::set;
using std::vector;
using std::cout;
using std::pair;
using std::string;
using std::endl;
using std::max;
using std::multimap;
using std::stringstream;

// error.cpp
int			error(string);
int			error(string, string);

// invalid_directive_len.cpp
bool		invalid_directive_len(std::vector<string> &, size_t, string, size_t, size_t);
bool		no_semicolon(std::vector<string> &, size_t &);

// set_ip_and_port.hpp
size_t		ft_atoi(string str);
size_t		set_port(string port);
string	    set_ip(string ip);

// print.cpp
void		print(int, const char *);
void		print(int code, const char *, const char *);

string	    itostring(int);
bool		only_digit(string str);

// check rights
bool	check_file_rights(const string &);
bool	is_a_file(const std::string &);
bool	is_a_dir(const std::string &);

#endif
