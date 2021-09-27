#include <iostream>
#include <string>
#include "Animal.hpp"

Animal::Animal( void )
{
	std::cout << "Animal was created by default constructor\n";
	this->type = "";
}

Animal::Animal( const Animal &animal )
{
	std::cout << "Animal was created by copy constructor\n";
	*this = animal;
}

Animal&	Animal::operator= ( const Animal &animal )
{
	std::cout << "Animal was created by asignment operator";
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
