#ifndef DIAMONDTRAP_HPP
# define DIAMONDTRAP_HPP

#include <string>
#include "FragTrap.hpp"
#include "ScavTrap.hpp"

class DiamondTrap: public ScavTrap, public FragTrap 
{
private:
	std::string	_name;
public:
	DiamondTrap( void );
	DiamondTrap( std::string name );
	~DiamondTrap();
	DiamondTrap&	operator =( const DiamondTrap &diamondtrap );
	using	FragTrap::_hitpoints;
	using	ScavTrap::_energy_points;
	using	FragTrap::_attack_damage;
	using	ScavTrap::attack;
	void	whoAmI( void );
};

#endif