#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"

class PhoneBook
{
  public:
	PhoneBook();
	bool addContact();
	void searchContacts() const;

  private:
	static const int MaxContacts = 8;
	Contact _contacts[MaxContacts];
	int _count;
	int _nextIndex;
};
#endif
