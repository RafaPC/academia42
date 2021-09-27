#include <string>
#include <iostream>
#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap( void )
{
	this->ClapTrap::_name = "Unnamed_clap_name";
	_name = "Unnamed";
	std::cout << _name << " evolved to a DiamondTrap!\n";
}

DiamondTrap::DiamondTrap( std::string name ): ClapTrap(name + "_clap_name"), _name(name)
{
	this->ClapTrap::_name = name + "_clap_name";
	std::cout << name << " evolved to a DiamondTrap!\n";
}

DiamondTrap::~DiamondTrap()
{
	std::cout << "DiamondTrap " << _name << " was destroyed\n";
}

DiamondTrap&	DiamondTrap::operator =( const DiamondTrap &scavtrap )
{
	std::cout << "DiamondTrap " << scavtrap._name << " duplicated!!!";
	this->ClapTrap::_name = scavtrap.ClapTrap::_name;
	_name = scavtrap._name;
	_attack_damage = scavtrap._attack_damage;
	_hitpoints = scavtrap._hitpoints;
	_energy_points = scavtrap._energy_points;
	return (*this);
}

void	DiamondTrap::whoAmI( void )
{
	std::cout << "Who are you, you ask me. Well...I used to be called "
	"" << this->ClapTrap::_name << " but now I prefer to be called " << _name << ".\n";
}
