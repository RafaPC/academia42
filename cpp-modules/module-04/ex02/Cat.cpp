#include <iostream>
#include "Cat.hpp"

Cat::Cat( void )
{
	this->type = "Cat";
	this->_brain = new Brain();
	this->_brain->ideas[0] = "Cat food";
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
	this->_brain = new Brain;
	*this->_brain = *cat._brain;
	return (*this);
}

Cat::~Cat()
{
	delete this->_brain;
	std::cout << "Cat was destroyed\n";
}

void		Cat::makeSound( void ) const
{
	std::cout << "Cat says Miauuuu\n";
}

std::string	Cat::getIdea( const int index ) const
{
	if (this->_brain == NULL)
		return ("This animal doesn't even have a brain\n");
	if (index >= 0 && index <= 100)
		return (this->_brain->ideas[index]);
	else
		return ("Wrong idea index");
}

void		Cat::changeIdea( const int index, const std::string idea)
{
	if (this->_brain && index >= 0 && index <= 100)
		this->_brain->ideas[index] = idea;
}
