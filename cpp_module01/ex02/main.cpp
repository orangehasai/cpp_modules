#include <iostream>
#include <string>

int main(void)
{
	const std::string str = "HI THIS IS BRAIN";
	const std::string *stringPTR = &str;
	const std::string &stringREF = str;

	std::cout << "pointer" << std::endl;
	std::cout << "variable:  " << &str << std::endl;
	std::cout << "stringPTR: " << stringPTR << std::endl;
	std::cout << "stringREF: " << &stringREF << std::endl;

	std::cout << "value" << std::endl;
	std::cout << "variable:  " << str << std::endl;
	std::cout << "stringPTR: " << *stringPTR << std::endl;
	std::cout << "stringREF: " << stringREF << std::endl;

	return 0;
}
