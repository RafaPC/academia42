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
		std::cout << zoo[i]->getIdea(0) << '\n';
	std::cout << "\nBrain deep copy test:\n";
	zoo[0]->getIdea(0);
	Animal animal = *(zoo[0]);
	std::cout << "Animal idea: " << zoo[0]->getIdea(0) << " - Other animal idea: " << animal.getIdea(0) << '\n';
	zoo[0]->changeIdea(0, "different food");
	std::cout << "Animal idea: " << zoo[0]->getIdea(0) << " - Other animal idea: " << animal.getIdea(0) << "\n\n";
	for (int i = 0; i < 50; i++)
		delete zoo[i];
	Animal* wrongcat = new WrongCat();
	std::cout << "WrongCat wrong sound: ";
	wrongcat->makeSound();
	std::cout << '\n';
	return (0);
}
