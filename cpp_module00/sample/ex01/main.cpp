#include "PhoneBook.hpp"
#include <iostream>
#include <string>

int	main(void)
{
	PhoneBook	phoneBook;
	std::string	command;

	std::cout << "Commands: ADD, SEARCH, EXIT" << std::endl;
	while (true)
	{
		std::cout << "> ";
		if (!std::getline(std::cin, command))
		{
			std::cout << std::endl;
			break ;
		}
		if (command == "ADD")
		{
			if (!phoneBook.addContact())
				break ;
		}
		else if (command == "SEARCH")
			phoneBook.searchContacts();
		else if (command == "EXIT")
			break ;
	}
	return (0);
}
