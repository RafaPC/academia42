#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

#include <string>

class ClapTrap
{
protected:
	std::string	_name;
	int			_hitpoints;
	int			_energy_points;
	int			_attack_damage;

public:
	ClapTrap( void );
	ClapTrap( std::string _name );
	ClapTrap( ClapTrap& obj );
	~ClapTrap();
	ClapTrap&	operator =( ClapTrap &claptrap );

	void	attack(std::string const &target);
	void	takeDamage(unsigned int amount);
	void	beRepaired(unsigned int amount);
};

#endif