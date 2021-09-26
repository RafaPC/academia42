#ifndef CAT_HPP
# define CAT_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Cat: public Animal
{
public:
	Cat( void );
	Cat(const Cat &Cat);
	Cat& operator =(const Cat &Cat);
	~Cat();
	void		makeSound( void ) const;
	std::string	getIdea( const int index ) const;
	void		changeIdea( const int index, const std::string idea );
private:
	Brain *_brain;
};

#endif