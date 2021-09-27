#include "ScavTrap.hpp"
#include <iostream>

int main( void )
{
	std::cout << "Scavtrap construction:\n";
	ScavTrap scavtrap("SC4V-TP");
	std::cout << '\n';

	scavtrap.guardGate();
	scavtrap.attack("a bandit");
	scavtrap.takeDamage(30);
	scavtrap.beRepaired(3);
	scavtrap.attack("another bandit");
	scavtrap.takeDamage(30);
	scavtrap.attack("a badass bandit");
	scavtrap.takeDamage(80);

	std::cout << "\nScavtrap destruction:\n";
	return 0;
}
