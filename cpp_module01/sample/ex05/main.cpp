#include "Harl.hpp"

#include <iostream>

int main(void)
{
	Harl harl;
	const std::string levels[5] = {
		"DEBUG",
		"INFO",
		"WARNING",
		"ERROR",
		"UNKNOWN"
	};

	for (int i = 0; i < 5; ++i)
	{
		harl.complain(levels[i]);
		if (i != 4)
			std::cout << std::endl;
	}

	return 0;
}
