#include <iostream>
#include "Cat.hpp"
#include "Dog.hpp"
#include "Animal.hpp"
#include "WrongCat.hpp"

int main( void )
{
	Animal* zoo[4];
	for (int i = 0; i < 2; i++)
		zoo[i] = new Dog();
	for (int i = 2; i < 4; i++)
		zoo[i] = new Cat();
	std::cout << "\nBrain deep copy test:\n";
	// creates new dog
	Dog *dog = new Dog();
	dog->getIdea(0);
	// creates copy of new dog
	Dog doggo = *dog;
	std::cout << "Dog idea: " << dog->getIdea(0) << " - Other dog idea: " << doggo.getIdea(0) << '\n';
	dog->changeIdea(0, "different food");
	std::cout << "Dog idea: " << dog->getIdea(0) << " - Other dog idea: " << doggo.getIdea(0) << "\n\n";
	delete dog;
	// delete the array of animals
	for (int i = 0; i < 4; i++)
		delete zoo[i];
	// wrongcast test
	std::cout << "\nWrongCat test:\n";
	Animal* wrongcat = new WrongCat();
	std::cout << "WrongCat wrong sound: ";
	wrongcat->makeSound();
	std::cout << '\n';
	delete wrongcat;
	return (0);
}
