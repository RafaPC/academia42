#include "Contact.hpp"

Contact::Contact(std::string first_name, std::string last_name,
	std::string nickname, std::string phone, std::string secret)
{
	this->first_name = first_name;
	this->last_name = last_name;
	this->nickname = nickname;
	this->phone_number = phone;
	this->darkest_secret = secret;
}
Contact::Contact(){}
