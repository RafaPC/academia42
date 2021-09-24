#include "Brain.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Brain::Brain( void )
{
	std::cout << "Brain was constructed\n";
	for (int i = 0; i < 100; i++)
		this->ideas[i] = "idea";
}

Brain::Brain( const Brain & src )
{
	std::cout << "Brain copied by reference\n";
	*this = src;
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Brain::~Brain()
{
	std::cout << "Brain was destroyed\n";
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Brain&				Brain::operator=( Brain const &brain )
{
	std::cout << "Brain copied by asignment operator. Ideas were copied from one to another\n";
	for (int i = 0; i < 100; i++)
		this->ideas[i] = brain.ideas[i];
	return *this;
}


/*
** --------------------------------- METHODS ----------------------------------
*/


/*
** --------------------------------- ACCESSOR ---------------------------------
*/

std::string	Brain::getIdea( void ) const
{
	return (this->ideas[0]);
}

void		Brain::changeIdea( const std::string idea)
{
	this->ideas[0] = idea;
}
/* ************************************************************************** */