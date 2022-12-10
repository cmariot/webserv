#include "Utils.hpp"

std::string	itostring(int nb)
{
	std::string	str;
	bool		negative = false;

	if (nb == 0)
		return ("0");
	else if (nb < 0)
	{
		negative = true;
		nb *= -1;
	}
	while (nb != 0)
	{
		str.insert(str.begin(), '0' + nb % 10);
		nb /= 10;
	}
	if (negative)
		str.insert(str.begin(), '-');
	return (str);
};
