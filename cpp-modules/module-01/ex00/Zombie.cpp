#include "Zombie.hpp"
#include <iostream>
#include <string>

Zombie::Zombie( void )
{
}

Zombie::~Zombie()
{
	std::cout << this->_name << " is destroyed\n";
}

void	Zombie::announce( void )
{
	std::cout << this->_name << " BraiiiiiiinnnzzzZ...\n";
}

void	Zombie::setName( std::string name )
{
	this->_name = name;
}