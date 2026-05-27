#include "PhoneBook.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

namespace
{
bool promptNonEmpty(const std::string &label, std::string &str)
{
	while (true)
	{
		std::cout << label;
		if (!std::getline(std::cin, str))
			return true;
		if (!str.empty())
			return false;
		std::cout << "This field cannot be empty." << std::endl;
	}
}

std::string formattedColumn(const std::string &str)
{
	if (str.length() <= 10)
		return str;
	return str.substr(0, 9) + ".";
}

bool parseInput(const std::string &input, int &index)
{
	char extra;
	std::istringstream iss(input);
	if (!(iss >> index))
		return false;
	if (iss >> extra)
		return false;
	return true;
}
} // namespace

PhoneBook::PhoneBook() : _count(0), _nextIndex(0)
{
}

bool PhoneBook::addContact()
{
	bool err;
	std::string firstName;
	std::string lastName;
	std::string nickname;
	std::string phoneNumber;
	std::string darkestSecret;
	err = promptNonEmpty("First Name: ", firstName);
	if (err)
		return false;
	err = promptNonEmpty("Last Name: ", lastName);
	if (err)
		return false;
	err = promptNonEmpty("Nickname: ", nickname);
	if (err)
		return false;
	err = promptNonEmpty("PhoneNumber: ", phoneNumber);
	if (err)
		return false;
	err = promptNonEmpty("Darkest Secret: ", darkestSecret);
	if (err)
		return false;
	_contacts[_nextIndex].setContact(firstName, lastName, nickname, phoneNumber, darkestSecret);
	if (_count < MaxContacts)
		++_count;
	_nextIndex = (_nextIndex + 1) % MaxContacts;
	std::cout << "Contact saved successfully." << std::endl;
	return true;
}

void PhoneBook::searchContacts() const
{
	std::string input;
	int index;
	if (_count == 0)
	{
		std::cout << "The phonebook is empty." << std::endl;
		return;
	}
	for (int i = 0; i < _count; ++i)
	{
		std::cout << std::setw(10) << i << "|";
		std::cout << std::setw(10) << formattedColumn(_contacts[i].getFirstName()) << "|";
		std::cout << std::setw(10) << formattedColumn(_contacts[i].getLastName()) << "|";
		std::cout << std::setw(10) << formattedColumn(_contacts[i].getnickname()) << "|"
				  << std::endl;
	}
	while (true)
	{
		std::cout << "Index to display: ";
		if (!std::getline(std::cin, input))
			return;
		if (!parseInput(input, index) || index < 0 || index >= _count)
			std::cout << "Invalid index." << std::endl;
		else
			break;
	}
	_contacts[index].displayDetail();
}
