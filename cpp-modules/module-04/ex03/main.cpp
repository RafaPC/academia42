#include "IMateriaSource.hpp"
#include "MateriaSource.hpp"
#include "ICharacter.hpp"
#include "Character.hpp"
#include "Ice.hpp"
#include "Cure.hpp"


int main()
{
	// creates materia source and learns 2 materias
	IMateriaSource* materia_source = new MateriaSource();
	materia_source->learnMateria(new Ice());
	materia_source->learnMateria(new Cure());
	// create character
	ICharacter* me = new Character("me");
	// creates materia pointer to store created materias
	AMateria* tmp_materia;
	// creates materia and stores it in tmp_materia, then equips into the character
	tmp_materia = materia_source->createMateria("ice");
	me->equip(tmp_materia);
	// the same but with another materia
	tmp_materia = materia_source->createMateria("cure");
	me->equip(tmp_materia);
	// creates another character on which to use the materias
	ICharacter* bob = new Character("bob");
	me->use(0, *bob);
	me->use(1, *bob);
	// unequips the ice materia
	me->unequip(0);
	// slots are filled from 0 to 1, so when the materia from the slot 0 is unequiped,
	// the rest of the materias are move one slot down
	me->use(0, *bob);
	delete bob;
	delete me;
	delete materia_source;
	system("leaks materias");
	return 0;
}