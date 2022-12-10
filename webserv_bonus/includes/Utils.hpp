#ifndef UTILS_HPP
# define UTILS_HPP

# define INFO 0
# define ERR 1
# define STDIN			0
# define STDOUT			1
# define STDERR			2
# define MAX_EVENTS		500
# define SIGNAL_CAUGHT	1
# define READY			1
# define INFO			0
# define BUFFER_SIZE	4096

# include <iostream>
# include <string>
# include <vector>
# include <map>
# include <set>
# include <sys/stat.h>
# include <sys/types.h>
# include <cstring>
# include <sstream>
# include <errno.h>
# include <sys/socket.h>
# include <netdb.h>
# include <fcntl.h>
# include <sys/epoll.h>
# include <cstring>
# include <utility>
# include <signal.h>
# include <cstdio>
# include <cstdlib>
# include <unistd.h>
# include <string>
# include <vector>
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
using std::string;
using std::cout;
using std::endl;

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
