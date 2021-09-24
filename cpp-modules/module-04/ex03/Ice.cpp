#include <iostream>
#include "Ice.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Ice::Ice()
{
	this->type = "ice";
}

Ice::Ice( const Ice & )
{
	type = "ice";
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Ice::~Ice()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Ice &				Ice::operator=( Ice const & )
{
	type = "ice";
	return *this;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

AMateria*	Ice::clone() const
{
	AMateria *materia = new Ice;
	return (materia);
}

void Ice::use(ICharacter& target)
{
	std::cout << "* shoots an ice bolt at " << target.getName() << " *\n";
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */