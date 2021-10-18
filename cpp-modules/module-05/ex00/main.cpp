#include <iostream>
#include "Bureaucrat.hpp"

int main( void )
{
	Bureaucrat	boss("Boss", 1);
	Bureaucrat	peasant("Peasant", 150);
	Bureaucrat	bureaucrat("Bureaucrat", 42);

	std::cout << boss << peasant << bureaucrat << '\n';
	try
	{
		std::cout << "Boss tries to increase his grade\n";
		boss.increaseGrade();
		std::cout << boss;
	}
	catch(const std::exception& e)
	{
		std::cout << "Error: " << e.what() << '\n';
	}

	try
	{
		std::cout << "Peasant tries to decrease his grade\n";
		peasant.decreaseGrade();
		std::cout << peasant;
	}
	catch(const std::exception& e)
	{
		std::cout << "Error: " << e.what() << '\n';
	}

	try
	{
		std::cout << "Bureaucrat tries to decrease his grade\n";
		bureaucrat.decreaseGrade();
		std::cout << bureaucrat;
	}
	catch(const std::exception& e)
	{
		std::cout << "Error: " << e.what() << '\n';
	}
	return 0;
}
