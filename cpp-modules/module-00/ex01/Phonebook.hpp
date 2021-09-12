#ifndef PHONEBOOK_H
#define PHONEBOOK_H

# include <string>
# include "Contact.hpp"

class Phonebook
{
private:
	void	print_trimmed_field(std::string field);
	void	display_contacts_table(void);
public:
	Contact contacts[8];
	short	contacts_length = 0;

	void	add_command(void);
	void	search_command(void);
};

#endif