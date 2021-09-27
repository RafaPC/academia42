#include <iostream>
#include "Cat.hpp"
#include "Dog.hpp"
#include "Animal.hpp"
#include "WrongCat.hpp"

int main( void )
{
	const Animal*	meta = new Animal();
	const Animal*	dog = new Dog();
	const Animal*	cat = new Cat();
	const WrongCat*	wrongcat = new WrongCat();

	std::cout << "\nTypes:\n";
	std::cout << "Animal type: " << meta->getType() << " \n";
	std::cout << "Cat type: " << cat->getType() << " \n";
	std::cout << "Dog type: " << dog->getType() << " \n";
	std::cout << "Wrongcat type: " << wrongcat->getType() << " \n\n";

	std::cout << "Sounds of animal, cat, dog and wrongcat\n";
	meta->makeSound();
	cat->makeSound();
	dog->makeSound();
	wrongcat->makeSound(); // will output the Animal sound because doesn't override the makeSound() method

	std::cout << "\nDestroying animal, dog, cat and wrongcat\n";
	std::cout << "\nAnimal:\n";
	delete meta;
	std::cout << "\nCat:\n";
	delete cat;
	std::cout << "\nDog:\n";
	delete dog;
	std::cout << "\nWrongCat:\n";
	delete wrongcat;
	return 0;
}
