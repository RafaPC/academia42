#ifndef ANIMAL_HPP
# define ANIMAL_HPP

#include <string>
#include "Brain.hpp"

class Animal
{
protected:
	Brain*	brain;
	std::string	type;
public:
	Animal( void );
	Animal( const Animal &animal );
	Animal&	operator =( const Animal &animal );
	virtual ~Animal();
	std::string		getType( void ) const;
	virtual void	makeSound( void )const ;
	std::string	getIdea( void )const;
};

#endif