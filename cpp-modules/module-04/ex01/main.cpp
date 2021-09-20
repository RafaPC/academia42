#include <iostream>
#include "Cat.hpp"
#include "Dog.hpp"
#include "Animal.hpp"
#include "WrongCat.hpp"

int main( void )
{
	const Animal* zoo[50];
	for (int i = 0; i < 25; i++)
		zoo[i] = new Dog();
	for (int i = 25; i < 50; i++)
		zoo[i] = new Cat();
	for (int i = 0; i < 50; i++)
		std::cout << zoo[i]->getIdea() << "\n";
	return 0;
}
