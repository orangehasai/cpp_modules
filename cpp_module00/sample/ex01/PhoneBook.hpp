#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include "Contact.hpp"

class PhoneBook
{
  public:
	PhoneBook(void);
	bool addContact(void);
	void searchContacts(void) const;

  private:
	static const int kMaxContacts = 8;

	Contact _contacts[kMaxContacts];
	int _count;
	int _nextIndex;
};

#endif
