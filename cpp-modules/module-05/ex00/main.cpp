#include <iostream>
#include "Bureaucrat.hpp"

int main( void )
{
	Bureaucrat boss("Boss", 1);
	Bureaucrat bureaucrat("Peasant", 150);

	std::cout << boss << bureaucrat;
	try
	{
		boss.increaseGrade();
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << '\n';
	}

	try
	{
		std::cout << "Peasant tries to decrease his grade\n";
		bureaucrat.decreaseGrade();
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
	return 0;
}
