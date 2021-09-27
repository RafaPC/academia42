#include "FragTrap.hpp"
#include <iostream>

int main( void )
{
	std::cout << "Fragtrap construction:\n";
	FragTrap fragtrap("FR4G-TP");
	std::cout << '\n';

	fragtrap.attack("a bandit");
	fragtrap.takeDamage(30);
	fragtrap.beRepaired(3);
	fragtrap.attack("another bandit");
	fragtrap.takeDamage(30);
	fragtrap.highFivesGuys();
	fragtrap.attack("a badass bandit");
	fragtrap.takeDamage(80);

	std::cout << "\nFragtrap destruction:\n";
	return 0;
}