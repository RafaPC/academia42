#include <iostream>
#include "Cat.hpp"

Cat::Cat( void )
{
	this->type = "Cat";
	std::cout << "Cat was created by default constructor\n";
}

Cat::Cat( const Cat &Cat )
{
	*this = Cat;
	std::cout << "Cat was created by copy constructor\n";
}

Cat&	Cat::operator= ( const Cat &Cat )
{
	this->type = Cat.type;
	return (*this);
}

Cat::~Cat()
{
	std::cout << "Cat was destroyed\n";
}

void	Cat::makeSound( void ) const
{
	std::cout << "Cat says Miauuuu\n";
}

