#include <string>
#include <iostream>
#include "FragTrap.hpp"

FragTrap::FragTrap( void )
{
	this->_name.assign("Unnamed");
	this->_hitpoints = 100;
	this->_energy_points = 100;
	this->_attack_damage = 30;
	std::cout << "FragTrap's default constructor has been called\n";
}

FragTrap::FragTrap( std::string _name ): ClapTrap(_name)
{
	this->_hitpoints = 100;
	this->_energy_points = 100;
	this->_attack_damage = 30;
	std::cout << _name << " evolved to a FragTrap!\n";
}

FragTrap::~FragTrap()
{
	std::cout << "FragTrap " << this->_name << " was destroyed\n";
}

FragTrap&	FragTrap::operator =( const FragTrap &scavtrap )
{
	std::cout << "Scavtrap " << scavtrap._name << " duplicated!!!";
	this->_name = scavtrap._name;
	this->_attack_damage = scavtrap._attack_damage;
	this->_hitpoints = scavtrap._hitpoints;
	this->_energy_points = scavtrap._energy_points;
	return (*this);
}

void	FragTrap::highFivesGuys( void )
{
	std::cout << "FragTrap " << this->_name << " says: GIMME FIVE!!\n";
}