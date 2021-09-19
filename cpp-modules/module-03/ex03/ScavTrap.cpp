#include <string>
#include <iostream>
#include "ScavTrap.hpp"

ScavTrap::ScavTrap( void )
{
	this->_name.assign("Unnamed");
	this->_hitpoints = 100;
	this->_energy_points = 50;
	this->_attack_damage = 20;
	std::cout << "ScravTrap's default constructor has been called\n";
}

ScavTrap::ScavTrap(std::string name): ClapTrap(name)
{
	this->_name = name;
	this->_hitpoints = 100;
	this->_energy_points = 50;
	this->_attack_damage = 20;
	std::cout << name << " evolved to a ScavTrap!\n";
}

ScavTrap::~ScavTrap()
{
	std::cout << "Scavtrap " << this->_name << " was destroyed\n";
}

ScavTrap&	ScavTrap::operator =( ScavTrap &scavtrap )
{
	std::cout << "ScavTrap " << scavtrap._name << " duplicated!!!";
	this->_name = scavtrap._name;
	this->_attack_damage = scavtrap._attack_damage;
	this->_hitpoints = scavtrap._hitpoints;
	this->_energy_points = scavtrap._energy_points;
	return (*this);
}

void	ScavTrap::guardGate( void )
{
	std::cout << "ScavTrap " << this->_name << " has entered Gate keeper mode\n";
}

void	ScavTrap::attack(std::string const &target)
{
	std::cout << "ScavTrap " << this->_name << " yeeted " << target << ""
	" causing it " << this->_attack_damage << " points of damage\n";
}