#include <iostream>
#include <string>

int main(void)
{
	std::string brain = "HI THIS IS BRAIN";
	std::string *stringPTR = &brain;
	std::string &stringREF = brain;

	std::cout << "Address of string variable : " << &brain << std::endl;
	std::cout << "Address stored in stringPTR: " << stringPTR << std::endl;
	std::cout << "Address of stringREF      : " << &stringREF << std::endl;

	std::cout << std::endl;

	std::cout << "Value of string variable   : " << brain << std::endl;
	std::cout << "Value pointed by stringPTR : " << *stringPTR << std::endl;
	std::cout << "Value referred by stringREF: " << stringREF << std::endl;

	return 0;
}
