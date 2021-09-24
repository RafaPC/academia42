#include "MateriaSource.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

MateriaSource::MateriaSource()
{
	this->_learned_materias_length = 0;
}

MateriaSource::MateriaSource( const MateriaSource & src )
{
	*this = src;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

MateriaSource::~MateriaSource()
{
	for (int i = 0; i < _learned_materias_length; i++)
		delete _learned_materias[i];
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

MateriaSource &				MateriaSource::operator=( MateriaSource const & other )
{
	_learned_materias_length = other._learned_materias_length;
	for (int i = 0; i < _learned_materias_length; i++)
		_learned_materias[i] = other._learned_materias[i]->clone();
	return *this;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void		MateriaSource::learnMateria(AMateria* materia)
{
	if (_learned_materias_length < 4)
	{
		_learned_materias[_learned_materias_length] = materia;
		_learned_materias_length++;
	}
}

AMateria*	MateriaSource::createMateria(std::string const & type)
{
	for (int i = 0; i < _learned_materias_length; i++)
	{
		if (_learned_materias[i]->getType() == type)
			return (_learned_materias[i]->clone());
	}
	return (NULL);
}

/* ************************************************************************** */