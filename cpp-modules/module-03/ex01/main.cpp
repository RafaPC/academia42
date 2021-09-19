#include "ScavTrap.hpp"

int main( void )
{
	ScavTrap scavtrap("SC4V-TP");

	scavtrap.guardGate();
	scavtrap.attack("a bandit");
	scavtrap.takeDamage(30);
	scavtrap.beRepaired(3);
	scavtrap.attack("another bandit");
	scavtrap.takeDamage(30);
	scavtrap.attack("a badass bandit");
	scavtrap.takeDamage(80);
	return 0;
}
