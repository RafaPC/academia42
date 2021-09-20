#include <iostream>
#include "Dog.hpp"

Dog::Dog( void )
{
	this->type = "Dog";
	std::cout << "Dog was created by default constructor\n";
}

Dog::Dog( const Dog &Dog )
{
	*this = Dog;
	std::cout << "Dog was created by copy constructor\n";
}

Dog&	Dog::operator= ( const Dog &Dog )
{
	this->type = Dog.type;
	return (*this);
}

Dog::~Dog()
{
	std::cout << "Dog was destroyed\n";
}

void	Dog::makeSound( void ) const
{
	std::cout << "Dog says Guau guau\n";
}

