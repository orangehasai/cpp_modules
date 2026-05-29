#include "replace.hpp"
#include <iostream>
#include <string>

static bool isValidArgs(int ac, char **av)
{
	const std::string s1 = av[2];
	if (ac != 4)
	{
		std::cout << "Usage: ./replace <filename> <s1> <s2>" << std::endl;
		return false;
	}
	if (!av[1] || !av[2] || !av[3])
	{
		return false;
	}
	if (s1.empty())
	{
		std::cout << "<s1> must not be empty" << std::endl;
		return false;
	}
	return true;
}

int main(int ac, char **av)
{
	if (!isValidArgs(ac, av))
		return (1);

	const std::string filename = av[1];
	const std::string s1 = av[2];
	const std::string s2 = av[3];
	if (!replaceFile(filename, s1, s2))
		return (1);
	return (0);
}
