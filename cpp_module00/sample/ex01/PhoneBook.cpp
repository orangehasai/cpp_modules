#include "PhoneBook.hpp"
#include <iomanip>
#include <iostream>
#include <sstream>

namespace
{
	std::string	promptNonEmptyField(const std::string &label, bool *ok)
	{
		std::string	value;

		while (true)
		{
			std::cout << label;
			if (!std::getline(std::cin, value))
			{
				*ok = false;
				return ("");
			}
			if (!value.empty())
			{
				*ok = true;
				return (value);
			}
			std::cout << "This field cannot be empty." << std::endl;
		}
	}

	std::string	formatColumn(const std::string &text)
	{
		if (text.length() <= 10)
			return (text);
		return (text.substr(0, 9) + ".");
	}

	bool	parseIndex(const std::string &input, int *index)
	{
		std::istringstream	iss(input);
		char				extra;

		if (!(iss >> *index))
			return (false);
		if (iss >> extra)
			return (false);
		return (true);
	}
}

PhoneBook::PhoneBook(void) : _count(0), _nextIndex(0)
{
}

bool	PhoneBook::addContact(void)
{
	bool		ok;
	std::string	firstName;
	std::string	lastName;
	std::string	nickname;
	std::string	phoneNumber;
	std::string	darkestSecret;

	firstName = promptNonEmptyField("First name: ", &ok);
	if (!ok)
		return (false);
	lastName = promptNonEmptyField("Last name: ", &ok);
	if (!ok)
		return (false);
	nickname = promptNonEmptyField("Nickname: ", &ok);
	if (!ok)
		return (false);
	phoneNumber = promptNonEmptyField("Phone number: ", &ok);
	if (!ok)
		return (false);
	darkestSecret = promptNonEmptyField("Darkest secret: ", &ok);
	if (!ok)
		return (false);
	_contacts[_nextIndex].setContact(firstName, lastName, nickname, phoneNumber,
		darkestSecret);
	if (_count < kMaxContacts)
		++_count;
	_nextIndex = (_nextIndex + 1) % kMaxContacts;
	std::cout << "Contact saved." << std::endl;
	return (true);
}

void	PhoneBook::searchContacts(void) const
{
	std::string	input;
	int			index;

	if (_count == 0)
	{
		std::cout << "The phonebook is empty." << std::endl;
		return ;
	}
	for (int i = 0; i < _count; ++i)
	{
		std::cout << std::setw(10) << i << "|";
		std::cout << std::setw(10)
			<< formatColumn(_contacts[i].getFirstName()) << "|";
		std::cout << std::setw(10)
			<< formatColumn(_contacts[i].getLastName()) << "|";
		std::cout << std::setw(10)
			<< formatColumn(_contacts[i].getNickname()) << std::endl;
	}
	std::cout << "Index to display: ";
	if (!std::getline(std::cin, input))
		return ;
	if (!parseIndex(input, &index) || index < 0 || index >= _count
		|| !_contacts[index].isStored())
	{
		std::cout << "Invalid index." << std::endl;
		return ;
	}
	_contacts[index].displayDetails();
}
