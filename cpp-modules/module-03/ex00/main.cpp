#include <iostream>
#include "ClapTrap.hpp"

int main( void )
{
	std::cout << "Claptrap construction:\n";
	ClapTrap claptrap("CL4P-TP");
	std::cout << '\n';

	claptrap.attack("a skag");
	claptrap.takeDamage(7);
	claptrap.beRepaired(3);
	claptrap.attack("another skag");
	claptrap.takeDamage(10);

	std::cout << "\nClaptrap destruction:\n";
	return 0;
}
