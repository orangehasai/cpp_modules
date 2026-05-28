#include "Zombie.hpp"

#include <iostream>

int main(void)
{
	const int count = 5;
	Zombie *horde = zombieHorde(count, "Walker");

	if (horde == 0)
	{
		std::cout << "Failed to create zombie horde." << std::endl;
		return 1;
	}

	for (int i = 0; i < count; ++i)
		horde[i].announce();

	delete[] horde;

	return 0;
}
