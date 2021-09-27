#ifndef ANIMAL_HPP
# define ANIMAL_HPP

#include <string>

class Animal
{
protected:
	std::string	type;
public:
	Animal( void );
	Animal( const Animal &animal );
	Animal&	operator =( const Animal &animal );
	virtual ~Animal();
	std::string		getType( void ) const;
	virtual void	makeSound( void )const = 0;
};

#endif