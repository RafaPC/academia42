#include <iostream>
#include "Cat.hpp"
#include "Dog.hpp"
#include "Animal.hpp"
#include "WrongCat.hpp"
#include <unistd.h>

int main( void )
{
	Animal* zoo[50];
	for (int i = 0; i < 25; i++)
		zoo[i] = new Dog();
	for (int i = 25; i < 50; i++)
		zoo[i] = new Cat();
	std::cout << "\n**** Dog and cat ideas: ****\n";
	for (int i = 0; i < 50; i++)
		std::cout << zoo[i]->getIdea() << '\n';
	std::cout << "\nBrain deep copy test:\n";
	zoo[0]->getIdea();
	Dog doggo = *((Dog*)(zoo[0]));
	std::cout << "Dog idea: " << zoo[0]->getIdea() << " - Other dog idea: " << doggo.getIdea() << '\n';
	zoo[0]->changeIdea("different food");
	std::cout << "Dog idea: " << zoo[0]->getIdea() << " - Other dog idea: " << doggo.getIdea() << "\n\n";
	for (int i = 0; i < 50; i++)
		delete zoo[i];
	return (0);
}
