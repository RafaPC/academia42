#include "DiamondTrap.hpp"

int main( void )
{
	DiamondTrap diamondtrap("D14M0ND-TP");

	diamondtrap.attack("a bandit");
	diamondtrap.takeDamage(30);
	diamondtrap.beRepaired(3);
	diamondtrap.attack("another bandit");
	diamondtrap.takeDamage(30);
	diamondtrap.attack("a badass bandit");
	diamondtrap.takeDamage(80);
	diamondtrap.highFivesGuys();
	diamondtrap.guardGate();
	diamondtrap.whoAmI();
	return 0;
}