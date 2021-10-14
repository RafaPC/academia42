#include <iostream>
#include "Bureaucrat.hpp"
#include "Form.hpp"

int main( void )
{
	Bureaucrat	bureaucrat1("Boss", 27);
	Bureaucrat	bureaucrat2("Peasant", 52);
	Form		form("form", 27, 50);

	std::cout << bureaucrat1 << bureaucrat2 << form << '\n';
	try
	{
		bureaucrat1.signForm(form);
	}
	catch (const std::exception &e)
	{
		std::cout << e.what();
	}
	try
	{
		bureaucrat2.signForm(form);
	}
	catch(const std::exception &e)
	{
		std::cout << e.what();
	}
	return 0;
}
