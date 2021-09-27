#include <string>
#include <iostream>
#include "FragTrap.hpp"

FragTrap::FragTrap( void )
{
	_name = ("Unnamed");
	_hitpoints = 100;
	_energy_points = 100;
	_attack_damage = 30;
	std::cout << "FragTrap's default constructor has been called\n";
}

FragTrap::FragTrap( std::string name ): ClapTrap(name)
{
	_hitpoints = 100;
	_energy_points = 100;
	_attack_damage = 30;
	std::cout << _name << " evolved to a FragTrap!\n";
}

FragTrap::~FragTrap()
{
	std::cout << "FragTrap " << _name << " was destroyed\n";
}

FragTrap&	FragTrap::operator =( const FragTrap &scavtrap )
{
	std::cout << "Scavtrap " << scavtrap._name << " duplicated!!!";
	_name = scavtrap._name;
	_attack_damage = scavtrap._attack_damage;
	_hitpoints = scavtrap._hitpoints;
	_energy_points = scavtrap._energy_points;
	return (*this);
}

void	FragTrap::highFivesGuys( void )
{
	std::cout << "FragTrap " << _name << " says: GIMME FIVE!!\n";
}