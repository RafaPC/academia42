#ifndef PHONEBOOK_H
#define PHONEBOOK_H

# include <string>
# include "Contact.hpp"

class Phonebook
{
public:
	Contact contacts[8];
	short	contacts_length = 0;

	void	addContact(std::string first_name, std::string last_name,
	std::string nickname, std::string phone, std::string secret);
	void	displayContacts(void);
};

#endif