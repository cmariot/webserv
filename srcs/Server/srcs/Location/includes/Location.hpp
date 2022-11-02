#ifndef LOCATION_HPP
# define LOCATION_HPP

# include <iostream>
# include <vector>
# include <string>

class Location
{
	public:

		Location()
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
