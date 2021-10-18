#include <iostream>
#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main( void )
{
	Bureaucrat	bureaucrat1("Bureaucrat1", 3);
	Bureaucrat	bureaucrat2("Bureaucrat2", 52);
	
	std::cout << bureaucrat1 << bureaucrat2 << '\n';

	/* FORMS */
	Form *shrubbery = new ShrubberyCreationForm("home");
	bureaucrat1.executeForm(*shrubbery);
	bureaucrat1.signForm(*shrubbery);
	bureaucrat1.executeForm(*shrubbery);
	std::cout << '\n';

	Form *robotomy = new RobotomyRequestForm("Robot");
	bureaucrat1.signForm(*robotomy);

	bureaucrat1.executeForm(*robotomy);
	bureaucrat2.executeForm(*robotomy);
	std::cout << '\n';

	Form *presidential = new PresidentialPardonForm();
	bureaucrat1.signForm(*presidential);
	bureaucrat1.executeForm(*presidential);


	delete shrubbery;
	delete robotomy;
	delete presidential;

	return 0;
}
