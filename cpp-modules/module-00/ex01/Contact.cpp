#include <iostream>
#include "Contact.hpp"

Contact::Contact(void){}

Contact::Contact(std::string first_name, std::string last_name,
	std::string nickname, std::string phone, std::string secret)
{
	this->first_name = first_name;
	this->last_name = last_name;
	this->nickname = nickname;
	this->phone_number = phone;
	this->darkest_secret = secret;
}

void	Contact::display_contact_information(void)
{
	std::cout << "\n-------------------------\n";
	std::cout << "First name: " << this->first_name << "\n";
	std::cout << "Last name: " << this->last_name << "\n";
	std::cout << "Nickname: " << this->nickname << "\n";
	std::cout << "Phone number: " << this->phone_number << "\n";
	std::cout << "Darkest secret: " << this->darkest_secret << "\n";
	std::cout << "-------------------------\n\n";
}
