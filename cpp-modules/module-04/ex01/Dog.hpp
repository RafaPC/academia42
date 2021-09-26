#ifndef DOG_HPP
# define DOG_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Dog: public Animal
{
public:
	Dog( void );
	Dog(const Dog &Dog);
	Dog& operator =(const Dog &Dog);
	~Dog();
	void		makeSound( void ) const;
	std::string	getIdea( const int index ) const;
	void		changeIdea( const int index, const std::string idea );
private:
	Brain *_brain;
};

#endif