#include <iostream>
#include "Cat.hpp"
#include "Dog.hpp"
#include "Animal.hpp"
#include <unistd.h>

int main( void )
{
	Animal* zoo[50];
	for (int i = 0; i < 25; i++)
		zoo[i] = new Dog();
	for (int i = 25; i < 50; i++)
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
	for (int i = 0; i < 50; i++)
		delete zoo[i];
	return (0);
}
