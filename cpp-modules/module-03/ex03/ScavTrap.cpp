#include <string>
#include <iostream>
#include "ScavTrap.hpp"

ScavTrap::ScavTrap( void )
{
	_name = "Unnamed";
	_hitpoints = 100;
	_energy_points = 50;
	_attack_damage = 20;
	std::cout << "ScravTrap's default constructor has been called\n";
}

ScavTrap::ScavTrap( std::string name ): ClapTrap(name)
{
	_hitpoints = 100;
	_energy_points = 50;
	_attack_damage = 20;
	std::cout << name << " evolved to a ScavTrap!\n";
}

ScavTrap::~ScavTrap()
{
	std::cout << "Scavtrap " << _name << " was destroyed\n";
}

ScavTrap&	ScavTrap::operator =( const ScavTrap &scavtrap )
{
	std::cout << "ScavTrap " << scavtrap._name << " duplicated!!!";
	_name = scavtrap._name;
	_attack_damage = scavtrap._attack_damage;
	_hitpoints = scavtrap._hitpoints;
	_energy_points = scavtrap._energy_points;
	return (*this);
}

void	ScavTrap::guardGate( void )
{
	std::cout << "ScavTrap " << _name << " has entered Gate keeper mode\n";
}

void	ScavTrap::attack( std::string const &target )
{
	if (_energy_points > 4)
	{
		std::cout << "ScavTrap " << _name << " yeets " << target << ""
		" causing it " << _attack_damage << " points of damage\n";
	}
	else
	{
		_energy_points -= 4;
		std::cout << "ScavTrap " << _name << " tries to yeet " << target << ""
		" but doesn't have enough energy.\n";
	}
	
}
