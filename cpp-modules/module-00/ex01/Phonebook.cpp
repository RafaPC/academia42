#include <iomanip>
#include <iostream>
#include "Phonebook.hpp"

void	Phonebook::display_contacts_table( void )
{
	Contact	current_contact;

	std::cout << "\nList of saved contacts.\n     INDEX|FIRST NAME| LAST NAME|  NICKNAME|\n";
	for (int i = 0; i < this->contacts_length; i++)
	{
		current_contact = this->contacts[i];
		std::cout << std::right << std::setw(10);
		std::cout << i << "|";
		this->print_trimmed_field(current_contact.first_name);
		this->print_trimmed_field(current_contact.last_name);
		this->print_trimmed_field(current_contact.nickname);
		std::cout << "\n";
	}
}

void	Phonebook::add_command( void )
{
	std::string	first_name, last_name, nickname, phone_number, darkest_secret;

	if (this->contacts_length == 8)
		std::cout << "The number of contacts has reached the limit, the oldest contact will be deleted\n";
	std::cout << "\nIntroduce each field when prompted.\n";
	std::cout << "First name: ";
	std::getline(std::cin, first_name);
	std::cout << "Last name: ";
	std::getline(std::cin, last_name);
	std::cout << "Nickname: ";
	std::getline(std::cin, nickname);
	std::cout << "Phone number: ";
	std::getline(std::cin, phone_number);
	std::cout << "Darkest secret: ";
	std::getline(std::cin, darkest_secret);

	Contact	newContact(first_name, last_name, nickname, phone_number, darkest_secret);
	short	i = this->contacts_length < 8 ? this->contacts_length : 7;
	while (i > 0)
	{
		this->contacts[i] = this->contacts[i - 1];
		i--;
	}
	this->contacts[0] = newContact;
	if (this->contacts_length < 8)
		this->contacts_length++;
	std::cout << "\nContact successfully added.\n\n";
}

void	Phonebook::search_command(void)
{
	if (this->contacts_length == 0)
	{
		std::cout << "\nThere are no contacts added\n";
		return ;
	}

	this->display_contacts_table();
	int			index;
	std::string	input;
	while (true) {
		std::cout << "\nEnter the index of the desired contact: ";
		std::getline(std::cin, input);
		try {
			index = std::stoi(input, NULL, 10);
			if (index >= 0 && index < this->contacts_length)
				break ;
			else
				std::cout << "Error: Index must be between 0 and "
				<< this->contacts_length - 1 << " (both included)\n";
		}
		catch (std::invalid_argument) { std::cout << "Error: Non numeric argument\n"; }
		catch (std::out_of_range) { std::cout << "Error: Index out of range of int\n"; }
	}
	this->contacts[index].display_contact_information();
}

void	Phonebook::print_trimmed_field(std::string field)
{
	if (field.length() <= 10)
	{
		std::cout << std::setw(10) << std::right;
		std::cout << field;
	}
	else
	{
		for (short i = 0; i < 9; i++)
			std::cout << field[i];
		std::cout << '.';
	}
	std::cout << "|";
}