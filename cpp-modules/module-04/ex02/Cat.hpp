#ifndef CAT_HPP
# define CAT_HPP

#include "Animal.hpp"

class Cat: public Animal
{
public:
	Cat( void );
	Cat(const Cat &Cat);
	Cat& operator =(const Cat &Cat);
	~Cat();
	void	makeSound( void ) const;
};

#endif