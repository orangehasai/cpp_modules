#include "Replace.hpp"

#include <iostream>

int main(int argc, char **argv)
{
	if (argc != 4)
	{
		std::cout << "Usage: ./replace <filename> <s1> <s2>" << std::endl;
		return 1;
	}

	const std::string filename = argv[1];
	const std::string s1 = argv[2];
	const std::string s2 = argv[3];

	if (s1.empty())
	{
		std::cout << "Error: s1 must not be empty." << std::endl;
		return 1;
	}

	std::string content;
	if (!readFile(filename, content))
	{
		std::cout << "Error: could not open " << filename << std::endl;
		return 1;
	}

	const std::string replaced = replaceAll(content, s1, s2);
	const std::string outputName = filename + ".replace";

	if (!writeFile(outputName, replaced))
	{
		std::cout << "Error: could not write " << outputName << std::endl;
		return 1;
	}

	std::cout << "Created " << outputName << std::endl;
	return 0;
}
