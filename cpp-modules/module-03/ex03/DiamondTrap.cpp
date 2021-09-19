#include <string>
#include <iostream>
#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap( void )
{
	this->ClapTrap::_name = "Unnamed_clap_name";
	this->_name = "Unnamed";
	std::cout << this->_name << " evolved to a DiamondTrap!\n";
}

DiamondTrap::DiamondTrap(std::string name): ClapTrap(name + "_clap_name"), _name(name)
{
	this->ClapTrap::_name = name + "_clap_name";
	std::cout << name << " evolved to a DiamondTrap!\n";
}

DiamondTrap::~DiamondTrap()
{
	std::cout << "DiamondTrap " << this->_name << " was destroyed\n";
}

DiamondTrap&	DiamondTrap::operator =( DiamondTrap &scavtrap )
{
	std::cout << "DiamondTrap " << scavtrap._name << " duplicated!!!";
	this->ClapTrap::_name = scavtrap.ClapTrap::_name;
	this->_name = scavtrap._name;
	this->_attack_damage = scavtrap._attack_damage;
	this->_hitpoints = scavtrap._hitpoints;
	this->_energy_points = scavtrap._energy_points;
	return (*this);
}

void	DiamondTrap::whoAmI( void )
{
	std::cout << "Who are you, you ask me. Well...I used to be called "
	"" << this->ClapTrap::_name << " but now I prefer to be called " << this->_name << ".\n";
}
