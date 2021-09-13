#include <string>
#include <iostream>
#include "HumanB.hpp"
#include "Weapon.hpp"

HumanB::HumanB( std::string name )
{
	this->weapon = NULL;
	this->name = name;
}

void	HumanB::attack( void )
{
	std::cout << this->name << " attacks with his "
	"" << ((this->weapon) ? this->weapon->getType() : "bare fists") << "\n";
}

void	HumanB::setWeapon( Weapon& weapon )
{
	this->weapon = &weapon;
}