#include <iostream>
#include "WrongCat.hpp"

WrongCat::WrongCat( void )
{
	this->type = "WrongCat";
	std::cout << "WrongCat was created by default constructor\n";
}

WrongCat::WrongCat( const WrongCat &WrongCat )
{
	*this = WrongCat;
	std::cout << "WrongCat was created by copy constructor\n";
}

WrongCat&	WrongCat::operator= ( const WrongCat &WrongCat )
{
	this->type = WrongCat.type;
	return (*this);
}

WrongCat::~WrongCat()
{
	std::cout << "WrongCat was destroyed\n";
}
