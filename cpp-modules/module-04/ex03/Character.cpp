#include "Character.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Character::Character( void )
{
	name = "Unnamed";
	_learned_materias_length = 0;
}

Character::Character( std::string name)
{
	this->name = name;
	_learned_materias_length = 0;
}

Character::Character( const Character & src )
{
	*this = src;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Character::~Character()
{
	for (int i = 0; i < _learned_materias_length; i++)
		delete inventory[i];
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Character &				Character::operator=( Character const &character )
{
	name = character.name;
	for (int i = 0; i < _learned_materias_length; i++)
		delete inventory[i];
	for (int i = 0; i < character._learned_materias_length; i++)
		inventory[i] = character.inventory[i]->clone();
	_learned_materias_length = character._learned_materias_length;
	return *this;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void	Character::use(int idx, ICharacter& target)
{
	if (idx >= 0 && idx < _learned_materias_length)
		this->inventory[idx]->use(target);
}

void	Character::equip(AMateria* m)
{
	if (_learned_materias_length < MAX_LEARNED_MATERIA_CAPACITY)
	{
		inventory[_learned_materias_length] = m;
		_learned_materias_length++;
	}
}

void	Character::unequip(int idx)
{
	if (idx >= 0 && idx < _learned_materias_length)
	{
		inventory[idx] = NULL;
		_learned_materias_length--;
		if (_learned_materias_length)
		{
			for (int i = idx; i < _learned_materias_length; i++)
				inventory[i] = inventory[i + 1];
			inventory[_learned_materias_length + 1] = NULL;
		}
	}
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

std::string const & Character::getName() const
{
	return name;
}

/* ************************************************************************** */