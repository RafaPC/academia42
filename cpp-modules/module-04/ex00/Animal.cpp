#include <iostream>
#include <string>
#include "Animal.hpp"

Animal::Animal( void )
{
	this->type = "";
	std::cout << "Animal unnamed was created\n";
}

Animal::Animal( const Animal &animal )
{
	*this = animal;
	std::cout << "Animal was created\n";
}

Animal&	Animal::operator= ( const Animal &animal )
{
	this->type = animal.type;
	return (*this);
}

Animal::~Animal()
{
	std::cout << "Animal was destroyed\n";
}

std::string	Animal::getType( void ) const
{
	return (this->type);
}

void	Animal::makeSound( void ) const
{
	std::cout << "Very strange sound\n";
}
