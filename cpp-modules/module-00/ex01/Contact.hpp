#ifndef CONTACT_H
#define CONTACT_H
# include <string>

class Contact
{
public:
	std::string first_name;
	std::string last_name;
	std::string nickname;
	std::string phone_number;
	std::string darkest_secret;

	Contact(std::string first_name, std::string last_name,
	std::string nickname, std::string phone, std::string secret);
	Contact(void);

	void	display_contact_information(void);
};

#endif