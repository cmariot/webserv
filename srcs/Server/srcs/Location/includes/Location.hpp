#ifndef LOCATION_HPP
# define LOCATION_HPP

# include <iostream>
# include <vector>
# include <string>

class Location
{
	public:

		std::string		uri;

		Location(std::string & uri) :
			uri(uri)
		{
			return ;
		};

		~Location()
		{
			return ;
		};

		int	parse_location(std::vector<std::string> &);
};

# endif
