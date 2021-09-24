#include <iostream>
#include <string>
#include "Animal.hpp"

Animal::Animal( void )
{
	this->type = "";
	this->brain = NULL;
	std::cout << "Animal was created by default constructor\n";
}

Animal::Animal( const Animal &animal )
{
	*this = animal;
	std::cout << "Animal was created by reference constructor\n";
}

Animal&	Animal::operator= ( const Animal &animal )
{
	this->type = animal.type;
	if (animal.brain)
	{
		this->brain = new Brain;
		*this->brain = *animal.brain;
	}
	else
		this->brain = NULL;
		std::cout << "Animal was created by = asignator\n";
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

std::string	Animal::getIdea( const int index ) const
{
	if (this->brain == NULL)
		return ("This animal doesn't even have a brain\n");
	if (index >= 0 && index <= 100)
		return (this->brain->ideas[index]);
	else
		return ("Wrong idea index");
}

void		Animal::changeIdea( const int index, const std::string idea)
{
	if (this->brain && index >= 0 && index <= 100)
		this->brain->ideas[index] = idea;
}
