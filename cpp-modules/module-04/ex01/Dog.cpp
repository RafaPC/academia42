#include <iostream>
#include "Dog.hpp"

Dog::Dog( void )
{
	this->type = "Dog";
	this->_brain = new Brain();
	this->_brain->ideas[0] = "Dog food";
	std::cout << "Dog was created by default constructor\n";
}

Dog::Dog( const Dog &Dog )
{
	*this = Dog;
	std::cout << "Dog was created by copy constructor\n";
}

Dog&	Dog::operator= ( const Dog &dog )
{
	this->type = dog.type;
	this->_brain = new Brain;
	*this->_brain = *dog._brain;
	return (*this);
}

Dog::~Dog()
{
	delete this->_brain;
	std::cout << "Dog was destroyed\n";
}

void		Dog::makeSound( void ) const
{
	std::cout << "Dog says Guau guau\n";
}

std::string	Dog::getIdea( const int index ) const
{
	if (this->_brain == NULL)
		return ("This animal doesn't even have a brain\n");
	if (index >= 0 && index <= 100)
		return (this->_brain->ideas[index]);
	else
		return ("Wrong idea index");
}

void		Dog::changeIdea( const int index, const std::string idea)
{
	if (this->_brain && index >= 0 && index <= 100)
		this->_brain->ideas[index] = idea;
}