#ifndef HUMANB_HPP
# define HUMANB_HPP
#include <string>
#include "Weapon.hpp"

class HumanB
{
public:
	Weapon		*weapon;
	std::string	name;

	HumanB( std::string name_ );
	void	attack( void );
	void	setWeapon( Weapon& weapon );
};
#endif