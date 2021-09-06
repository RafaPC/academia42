#include <iostream>
#include <string>
#include <iomanip>
#include <exception>
#include "Phonebook.hpp"

void	add_command(Phonebook *phonebook);
void	search_command(Phonebook phonebook);

int main(void)
{
	std::string  	input;
	Phonebook phonebook;

	while (true)
	{
		std::cout << "Waiting for command: ";
		std::cin >> input;
		if (input == "ADD")
			add_command(&phonebook);
		else if (input == "SEARCH")
			search_command(phonebook);
		else if (input == "EXIT")
			return (0);
		else
			std::cout << "Invalid input\n";
	}

	return (0);
}

void	add_command(Phonebook *phonebook)
{
	std::string first_name;
	std::string last_name;
	std::string nickname;
	std::string phone_number;
	std::string darkest_secret;
	if (phonebook->contacts_length == 8)
		std::cout << "The number of contacts has reached the limit,the oldest contact will be deleted\n";
	std::cout << "First name: ";
	std::cin >> first_name;
	std::cout << "Last name: ";
	std::cin >> last_name;
	std::cout << "Nickname: ";
	std::cin >> nickname;
	std::cout << "Phone number: ";
	std::cin >> phone_number;
	std::cout << "Darkest secret: ";
	std::cin >> darkest_secret;
	phonebook->addContact(first_name, last_name, nickname, phone_number, darkest_secret);
}

void	search_command(Phonebook phonebook)
{
	std::string	input;
	int			index;

	if (phonebook.contacts_length == 0)
	{
		std::cout << "There are no contacts added\n";
		return ;
	}
	phonebook.displayContacts();
	while (true) {
		std::cout << "Index: ";
		std::getline(std::cin, input);
		try {
			index = std::stoi(input, NULL, 10);
			if (index >= 0 && index < phonebook.contacts_length)
				break ;
			else
				std::cerr << "Error: Index must be between 0 and "
				<< phonebook.contacts_length - 1 << " (both included)\n";
		}
		catch (std::invalid_argument) { std::cerr << "Error: Non numeric argument\n"; }
		catch (std::out_of_range) { std::cerr << "Error: Index out of range of int\n"; }
	}
	std::cout << "First name: " << phonebook.contacts[index].first_name << "\n";
	std::cout << "Last name: " << phonebook.contacts[index].last_name << "\n";
	std::cout << "Nickname: " << phonebook.contacts[index].nickname << "\n";
	std::cout << "Phone number: " << phonebook.contacts[index].phone_number << "\n";
	std::cout << "Darkest secret: " << phonebook.contacts[index].darkest_secret << "\n";
}
