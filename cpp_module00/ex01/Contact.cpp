#include "Contact.hpp"
#include <iostream>

Contact::Contact()
	: _firstName(""), _lastName(""), _nickname(""), _phoneNumber(""), _darkestSecret("")
{
}

void Contact::setContact(const std::string &firstName, const std::string &lastName,
						 const std::string &nickname, const std::string &phoneNumber,
						 const std::string &darkestSecret)
{
	_firstName = firstName;
	_lastName = lastName;
	_nickname = nickname;
	_phoneNumber = phoneNumber;
	_darkestSecret = darkestSecret;
}

const std::string Contact::getFirstName() const
{
	return _firstName;
}

const std::string Contact::getLastName() const
{
	return _lastName;
}

const std::string Contact::getnickname() const
{
	return _nickname;
}

void Contact::displayDetail() const
{
	std::cout << "First name: " << _firstName << std::endl;
	std::cout << "Last name: " << _lastName << std::endl;
	std::cout << "nickname: " << _nickname << std::endl;
	std::cout << "Phone number: " << _phoneNumber << std::endl;
	std::cout << "Darkest secret: " << _darkestSecret << std::endl;
}
