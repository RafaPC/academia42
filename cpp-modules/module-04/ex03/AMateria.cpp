#include "AMateria.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

AMateria::AMateria()
{
	this->type = "no_type";
}

AMateria::AMateria(std::string const & type)
{
	this->type = type;
}

AMateria::AMateria( const AMateria & src )
{
	*this = src;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

AMateria::~AMateria()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

AMateria&				AMateria::operator=( AMateria const &other )
{
	type = other.type;
	return *this;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void		AMateria::use(ICharacter& target)
{
	(void)target;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

std::string	const & AMateria::getType() const
{
	return type;
}

/* ************************************************************************** */