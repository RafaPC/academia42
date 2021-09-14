#include <iostream>
#include "Fixed.hpp"


Fixed::Fixed()
{
	this->value = 0;
	std::cout << "Default constructor called\n";
}

Fixed::Fixed( Fixed& fixed_obj)
{
	std::cout << "Copy constructor called\n";
	*this = fixed_obj;
}

Fixed::~Fixed()
{
	std::cout << "Destructor called\n";
}

void	Fixed::operator = ( const Fixed &fixed )
{
	std::cout << "Assignation operator called\n";
	this->value = fixed.getRawBits();
}

int	Fixed::getRawBits( void ) const
{
	std::cout << "getRawBits member funcion called\n";
	return (this->value);
}

void	Fixed::setRawBits( int const raw )
{
	this->value = raw;
}
