#include <iostream>
#include <string>
#include "Animal.hpp"

Animal::Animal( void )
{
	this->type = "";
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
