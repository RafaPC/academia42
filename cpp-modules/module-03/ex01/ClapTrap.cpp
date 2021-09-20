#include <iostream>
#include "ClapTrap.hpp"

ClapTrap::ClapTrap( void ): _name("Noname"), _hitpoints(10), _energy_points(10), _attack_damage(0)
{
	std::cout << "Default constructor has been called\n";
}

ClapTrap::ClapTrap( std::string _name ): _name("Noname"), _hitpoints(10), _energy_points(10), _attack_damage(0)
{
	std::cout << "Wild " << _name << " appeared!\n";
}

ClapTrap::ClapTrap( ClapTrap& obj )
{
	std::cout << obj._name << " just duplicated, wtf\n"; 
	*this = obj;
}

ClapTrap::~ClapTrap()
{
	std::cout << "Claptrap " << this->_name << " died peacefully\n";
}

ClapTrap&	ClapTrap::operator =( const ClapTrap &claptrap )
{
	this->_name = claptrap._name;
	this->_hitpoints = claptrap._hitpoints;
	this->_energy_points = claptrap._energy_points;
	this->_attack_damage = claptrap._attack_damage;
	return (*this);
}

void	ClapTrap::attack( std::string const &target )
{
	if (this->_energy_points < 2)
		std::cout << this->_name << " tries to attack but fails because doesn't have enough energy\n";
	else
	{
		this->_energy_points -= 2;
		std::cout << this->_name << " attacks " << target << ""
		", causing " << this->_attack_damage << " points of damage\n";
	}
}

void	ClapTrap::takeDamage( unsigned int amount )
{
	this->_hitpoints -= amount;
	if (this->_hitpoints > 0)
		std::cout << this->_name << " receives " << amount << " points of damage but survives\n";
	else
		std::cout << this->_name << " received " << amount << " points of damage and died\n";
}

void	ClapTrap::beRepaired( unsigned int amount )
{
	this->_hitpoints += amount;
	std::cout << this->_name << " is repaired and gains " << amount << " _hitpoints\n";
}
