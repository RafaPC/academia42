#ifndef HUMANA_HPP
# define HUMANA_HPP
# include <string>
# include "Weapon.hpp"

class HumanA
{
public:
	std::string	name;
	Weapon&		weapon;

	HumanA( std::string name_, Weapon& weapon_ );
	void	attack(void);
};
#endif