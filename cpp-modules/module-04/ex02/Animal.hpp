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
	virtual void	makeSound( void )const  = 0;
	std::string		getIdea( const int index )const;
	void			changeIdea( const int index, const std::string idea );
};

#endif