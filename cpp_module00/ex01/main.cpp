#include "PhoneBook.hpp"
#include <iostream>
#include <string>

int main()
{
	std::string command;
	PhoneBook phoneBook;

	std::cout << "Commands: ADD, SEARCH, EXIT" << std::endl;
	while (true)
	{
		std::cout << "> ";
		if (!getline(std::cin, command))
			return 1;
		if (command == "ADD")
		{
			if (!phoneBook.addContact())
				return 0;
		}
		else if (command == "SEARCH")
			phoneBook.searchContacts();
		else if (command == "EXIT")
		{
			std::cout << "Bye" << std::endl;
			return 0;
		}
		else
			std::cout << "Commands: ADD, SEARCH, EXIT" << std::endl;
	}
}
