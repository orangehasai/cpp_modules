#include "Zombie.hpp"
#include <iostream>
#include <sstream>

namespace
{
bool parsePositiveInt(const char *text, int &value)
{
	std::istringstream iss(text);
	iss >> value;
	return !iss.fail() && iss.eof() && value > 0;
}
} // namespace

int main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cout << "Usage: ./zombie <count> <name>" << std::endl;
		return 1;
	}
	int N;
	if (!parsePositiveInt(av[1], N))
	{
		std::cout << "count must be a positive integer" << std::endl;
		return 1;
	}
	const std::string name = av[2];
	Zombie *zombies;

	zombies = zombieHorde(N, name);
	if (zombies == 0)
	{
		std::cout << "Zombie creation festival is unfortunately failed" << std::endl;
		return 1;
	}

	for (int i = 0; i < N; ++i)
		zombies[i].announce();

	delete[] zombies;
	return 0;
}
