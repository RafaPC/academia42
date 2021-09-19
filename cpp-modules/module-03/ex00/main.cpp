#include "ClapTrap.hpp"

int main( void )
{
	ClapTrap claptrap("CL4P-TP");

	claptrap.attack("a skag");
	claptrap.takeDamage(7);
	claptrap.beRepaired(3);
	claptrap.attack("another skag");
	claptrap.takeDamage(10);
	return 0;
}
