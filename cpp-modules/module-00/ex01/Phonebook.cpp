#include <string>
#include <ios>
#include <iomanip>
#include <iostream>
#include "Phonebook.hpp"

void	Phonebook::addContact(std::string first_name, std::string last_name,
std::string nickname, std::string phone, std::string secret)
{
	Contact newContact(first_name, last_name, nickname, phone, secret);

	// FIXME:
	// if (this->contacts_length > 0 && this->contacts_length < 8)
	// 	this->contacts[this->contacts_length] = newContact;
	short	i = this->contacts_length < 8 ? this->contacts_length : 7;
	while (i > 0)
	{
		this->contacts[i] = this->contacts[i - 1];
		i--;
	}
	this->contacts[0] = newContact;
	if (this->contacts_length < 8)
		this->contacts_length++;
}

void	Phonebook::displayContacts(void)
{
	Contact	current_contact;

	std::cout << "     INDEX|FIRST NAME| LAST NAME|  NICKNAME|\n";
	for (int i = 0; i < this->contacts_length; i++)
	{
		//FIXME: probar con strings de 10 carácteres justos
		current_contact = this->contacts[i];
		current_contact.first_name = current_contact.first_name.substr(0, 10);
		if (current_contact.first_name.length() == 10)
			current_contact.first_name[9] = '.';
		current_contact.last_name = current_contact.last_name.substr(0, 10);
		if (current_contact.last_name.length() == 10)
			current_contact.last_name[9] = '.';
		current_contact.nickname = current_contact.nickname.substr(0, 10);
		if (current_contact.nickname.length() == 10)
			current_contact.nickname[9] = '.';
		std::cout << std::right << std::setw(10);
		std::cout << i << "|";
		std::cout << std::right << std::setw(10);
		std::cout << current_contact.first_name << "|";
		std::cout << std::right << std::setw(10);
		std::cout << current_contact.last_name << "|";
		std::cout << std::right << std::setw(10);
		std::cout << current_contact.nickname << "|\n";
	}
}
