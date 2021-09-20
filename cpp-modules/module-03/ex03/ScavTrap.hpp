#ifndef SCAVTRAP_HPP
# define SCAVTRAP_HPP

#include <string>
#include "ClapTrap.hpp"

class ScavTrap: public virtual ClapTrap
{
public:
	ScavTrap( void );
	ScavTrap( std::string name );
	~ScavTrap();
	ScavTrap&	operator =( const ScavTrap &scavtrap );
	void	guardGate( void );
	void	attack( std::string const &target );
};

#endif