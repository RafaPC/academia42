#include "DiamondTrap.hpp"
#include <iostream>

int main( void )
{
	std::cout << "Diamondtrap construction:\n";
	DiamondTrap diamondtrap("D14M0ND-TP");
	std::cout << "\n";

	diamondtrap.attack("a bandit");
	diamondtrap.takeDamage(30);
	diamondtrap.beRepaired(3);
	diamondtrap.attack("another bandit");
	diamondtrap.takeDamage(30);
	diamondtrap.attack("a badass bandit");
	diamondtrap.takeDamage(80);

	std::cout << "\nSpecial functions:\n";
	diamondtrap.highFivesGuys();
	diamondtrap.guardGate();
	diamondtrap.whoAmI();
	std::cout << "\nDiamondtrap destruction:\n";
	return 0;
}