#include <cctype>
#include <iostream>
#include <string>

static std::string strtoupper(const std::string &text)
{
	unsigned char	uc;

	std::string result;
	for (int i = 0; text[i]; ++i)
	{
		uc = static_cast<unsigned char>(text[i]);
		result += static_cast<char>(std::toupper(uc));
	}
	return (result);
}

int	main(int ac, char **av)
{
	if (ac == 1)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return (0);
	}
	for (int i = 1; i < ac; ++i)
		std::cout << strtoupper(av[i]);
	std::cout << std::endl;
	return (0);
}
