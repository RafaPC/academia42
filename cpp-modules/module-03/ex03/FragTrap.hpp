#ifndef FRAGTRAP_HPP
# define FRAGTRAP_HPP

#include <string>
#include "ClapTrap.hpp"

class FragTrap: public virtual ClapTrap
{
public:
	FragTrap( void );
	FragTrap(std::string name);
	~FragTrap();
	FragTrap&	operator =( FragTrap &fragtrap );
	void	highFivesGuys( void );
};

#endif