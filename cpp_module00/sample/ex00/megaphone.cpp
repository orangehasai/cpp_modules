#include <cctype>
#include <iostream>
#include <string>

static std::string toUpperCopy(const std::string &text)
{
	unsigned char	current;

	std::string result;
	for (int i = 0; text[i] != '\0'; ++i)
	{
		current = static_cast<unsigned char>(text[i]);
		result += static_cast<char>(std::toupper(current));
	}
	return (result);
}

int	main(int argc, char **argv)
{
	if (argc == 1)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return (0);
	}
	for (int i = 1; i < argc; ++i)
		std::cout << toUpperCopy(argv[i]);
	std::cout << std::endl;
	return (0);
}
