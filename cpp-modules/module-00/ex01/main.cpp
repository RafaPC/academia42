#include <iostream>
#include <string>
#include <iomanip>
#include "Phonebook.hpp"

int main(void)
{
	std::string	input;
	Phonebook	phonebook;

	while (true)
	{
		std::cout << "Waiting for command: ";
		std::getline(std::cin, input);
		if (input == "ADD")
			phonebook.add_command();
		else if (input == "SEARCH")
			phonebook.search_command();
		else if (input == "EXIT")
			return (0);
		else
			std::cout << "Invalid input\n";
	}
	return (0);
}
