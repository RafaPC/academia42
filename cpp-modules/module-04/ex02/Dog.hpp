#ifndef DOG_HPP
# define DOG_HPP

#include "Animal.hpp"

class Dog: public Animal
{
public:
	Dog( void );
	Dog(const Dog &Dog);
	Dog& operator =(const Dog &Dog);
	~Dog();
	void	makeSound( void ) const;
};

#endif