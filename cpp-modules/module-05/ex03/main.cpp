#include <iostream>
#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

int main( void )
{
	Intern		intern;
	Bureaucrat	bureaucrat1("Bureaucrat1", 3);
	Bureaucrat	bureaucrat2("Bureaucrat2", 52);
	
	std::cout << bureaucrat1 << bureaucrat2 << '\n';

	/* FORMS */
	Form	*shrubbery = intern.makeForm("shrubbery creation", "home");
	bureaucrat1.executeForm(*shrubbery);
	bureaucrat1.signForm(*shrubbery);
	bureaucrat1.executeForm(*shrubbery);
	std::cout << '\n';

	Form *robotomy = intern.makeForm("robotomy request", "Bender");
	bureaucrat1.signForm(*robotomy);
	bureaucrat1.executeForm(*robotomy);
	bureaucrat2.executeForm(*robotomy);
	std::cout << '\n';

	Form *presidential = intern.makeForm("presidential pardon", "Jhon Doe");
	bureaucrat1.signForm(*presidential);
	bureaucrat1.executeForm(*presidential);
	std::cout << '\n';

	Form *whatever = intern.makeForm("invent form", "Whatever");
	(void)whatever;

	delete shrubbery;
	delete robotomy;
	delete presidential;

	return 0;
}
