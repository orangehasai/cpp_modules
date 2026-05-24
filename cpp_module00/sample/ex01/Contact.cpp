#include "Contact.hpp"
#include <iostream>

Contact::Contact(void) : _firstName(""), _lastName(""), _nickname(""),
	_phoneNumber(""), _darkestSecret(""), _isStored(false)
{
}

void Contact::setContact(const std::string &firstName,
	const std::string &lastName, const std::string &nickname,
	const std::string &phoneNumber, const std::string &darkestSecret)
{
	_firstName = firstName;
	_lastName = lastName;
	_nickname = nickname;
	_phoneNumber = phoneNumber;
	_darkestSecret = darkestSecret;
	_isStored = true;
}

bool Contact::isStored(void) const
{
	return (_isStored);
}

const std::string &Contact::getFirstName(void) const
{
	return (_firstName);
}

const std::string &Contact::getLastName(void) const
{
	return (_lastName);
}

const std::string &Contact::getNickname(void) const
{
	return (_nickname);
}

void Contact::displayDetails(void) const
{
	std::cout << "First name: " << _firstName << std::endl;
	std::cout << "Last name: " << _lastName << std::endl;
	std::cout << "Nickname: " << _nickname << std::endl;
	std::cout << "Phone number: " << _phoneNumber << std::endl;
	std::cout << "Darkest secret: " << _darkestSecret << std::endl;
}
