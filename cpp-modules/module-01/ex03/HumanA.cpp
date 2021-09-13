#include <iostream>
#include "HumanA.hpp"

HumanA::HumanA( std::string name_, Weapon& weapon_ ) : name(name_), weapon(weapon_) {}

void	HumanA::attack(void)
{
	std::cout << this->name << " attacks with his " << this->weapon.getType() << "\n";
}

