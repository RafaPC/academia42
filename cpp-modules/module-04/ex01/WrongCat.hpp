#ifndef WRONGCAT_HPP
# define WRONGCAT_HPP

#include "Animal.hpp"

class WrongCat: public Animal
{
public:
	WrongCat( void );
	WrongCat(const WrongCat &wrongcat);
	WrongCat& operator =(const WrongCat &Wrongcat);
	~WrongCat();
};

#endif