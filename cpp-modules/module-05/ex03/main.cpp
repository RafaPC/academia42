#include <iostream>
#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

int main( void )
{
	Intern		intern;
	Bureaucrat	bureaucrat1("Boss", 3);
	Bureaucrat	bureaucrat2("Peasant", 52);
	
	std::cout << bureaucrat1 << bureaucrat2 << '\n';

	/* FORMS */
	Form	*shrubbery = intern.makeForm("shrubbery creation", "home");
	bureaucrat1.executeForm(*shrubbery);
	bureaucrat1.signForm(*shrubbery);
	bureaucrat1.executeForm(*shrubbery);

	Form *robotomy = intern.makeForm("robotomy request", "Bender");
	bureaucrat1.signForm(*robotomy);
	bureaucrat1.executeForm(*robotomy);
	bureaucrat2.executeForm(*robotomy);

	Form *presidential = intern.makeForm("presidential pardon", "Jhon Doe");
	bureaucrat1.signForm(*presidential);
	bureaucrat1.executeForm(*presidential);


	delete shrubbery;
	delete robotomy;
	delete presidential;

	return 0;
}
