#include "FragTrap.hpp"

int main( void )
{
	FragTrap fragtrap("FR4G-TP");

	fragtrap.attack("a bandit");
	fragtrap.takeDamage(30);
	fragtrap.beRepaired(3);
	fragtrap.attack("another bandit");
	fragtrap.takeDamage(30);
	fragtrap.highFivesGuys();
	fragtrap.attack("a badass bandit");
	fragtrap.takeDamage(80);
	return 0;
}