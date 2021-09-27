#include <iostream>
#include "Cure.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Cure::Cure()
{
	type = "cure";
}

Cure::Cure( const Cure & )
{
	type = "cure";
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Cure::~Cure()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Cure &		Cure::operator=( Cure const & )
{
	type = "cure";
	return *this;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

AMateria*	Cure::clone() const
{
	AMateria *materia = new Cure;
	return (materia);
}

void		Cure::use(ICharacter& target)
{
	std::cout << "* heals " << target.getName() << "'s wounds *\n";
}
/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */