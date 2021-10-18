#include "RobotomyRequestForm.hpp"
#include <cstdlib>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

RobotomyRequestForm::RobotomyRequestForm( std::string target ):
Form("Robotomy Request Form", 72, 45, target)
{
}

RobotomyRequestForm::RobotomyRequestForm( const RobotomyRequestForm & src )
{
	(void)src;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

RobotomyRequestForm::~RobotomyRequestForm()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

RobotomyRequestForm &				RobotomyRequestForm::operator=( RobotomyRequestForm const & rhs )
{
	(void)rhs;
	return *this;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void				RobotomyRequestForm::executeAction( void ) const
{
	srand(time(NULL));
	std::cout << "* Drilling noises *\n";
	if (rand() % 2)
		std::cout << getTarget() << " has been robotomized successfully\n";
	else
		std::cout << getTarget() << " robotomy was a failure\n";
}

/* ************************************************************************** */