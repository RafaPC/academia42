#include <iostream>
#include <string>
#include "Animal.hpp"

Animal::Animal( void )
{
	this->type = "";
	this->brain = NULL;
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
	this->brain = animal.brain;
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

std::string	Animal::getIdea( void )const
{
	if (this->brain)
		return (this->brain->getIdea());
	else
		return ("no idea");
}
