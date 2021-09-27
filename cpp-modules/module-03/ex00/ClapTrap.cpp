#include <iostream>
#include "ClapTrap.hpp"

ClapTrap::ClapTrap( void ): _name("Noname"), _hitpoints(10), _energy_points(10), _attack_damage(0)
{
	std::cout << "Default claptrap constructor has been called\n";
}

ClapTrap::ClapTrap( std::string name ): _name(name), _hitpoints(10), _energy_points(10), _attack_damage(0)
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
	_name = claptrap._name;
	_hitpoints = claptrap._hitpoints;
	_energy_points = claptrap._energy_points;
	_attack_damage = claptrap._attack_damage;
	return (*this);
}

void	ClapTrap::attack( std::string const &target )
{
	if (_energy_points < 2)
		std::cout << _name << " tries to attack but fails because doesn't have enough energy\n";
	else
	{
		_energy_points -= 2;
		std::cout << _name << " attacks " << target << ""
		", causing " << _attack_damage << " points of damage\n";
	}
}

void	ClapTrap::takeDamage( unsigned int amount )
{
	_hitpoints -= amount;
	if (_hitpoints > 0)
		std::cout << _name << " receives " << amount << " points of damage but survives\n";
	else
		std::cout << _name << " received " << amount << " points of damage and died\n";
}

void	ClapTrap::beRepaired( unsigned int amount )
{
	_hitpoints += amount;
	std::cout << _name << " is repaired and gains " << amount << "  hitpoints\n";
}
