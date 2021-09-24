#include <iostream>
#include "Cat.hpp"

Cat::Cat( void )
{
	this->type = "Cat";
	this->brain = new Brain();
	this->brain->ideas[0] = "Cat food";
	std::cout << "Cat was created by default constructor\n";
}

Cat::Cat( const Cat &Cat )
{
	*this = Cat;
	std::cout << "Cat was created by copy constructor\n";
}

Cat&	Cat::operator= ( const Cat &cat )
{
	this->type = cat.type;
	this->brain = new Brain;
	this->brain = cat.brain;
	return (*this);
}

Cat::~Cat()
{
	delete this->brain;
	std::cout << "Cat was destroyed\n";
}

void	Cat::makeSound( void ) const
{
	std::cout << "Cat says Miauuuu\n";
}

