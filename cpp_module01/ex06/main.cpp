#include "Harl.hpp"

#include <iostream>

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Usage: ./harlFilter <level>" << std::endl;
		return 1;
	}
	Harl harl;
	const std::string level = av[1];
	harl.complain(level);
	return 0;
}
