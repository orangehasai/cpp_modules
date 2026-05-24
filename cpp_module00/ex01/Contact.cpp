#include "Contact.hpp"

Contact::Contact() : _firstName(""), _lastName(""), _nickname(""),
	_phoneNumber(""), _darkestSecret("")
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
}

const std::string Contact::getFirstName(void) const
{
	return (_firstName);
}

const std::string Contact::getLastname(void) const
{
	return (_lastName);
}

const std::string Contact::getnickname(void) const
{
	return (_nickname);
}

void Contact::displayDetail() const
{
}