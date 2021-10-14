#include "Bureaucrat.hpp"
#include "Form.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Bureaucrat::Bureaucrat(std::string name, int grade): _name(name), _grade(grade)
{
	if (grade < 1)
		throw GradeTooHighException();
	else if (grade > 150)
		throw GradeTooLowException();
}

Bureaucrat::Bureaucrat( const Bureaucrat & other ): _name(other._name)
{
	if (other._grade < 1)
		throw Bureaucrat::GradeTooHighException();
	else if (other._grade > 150)
		throw Bureaucrat::GradeTooLowException();
	else
		this->_grade = other._grade;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Bureaucrat::~Bureaucrat()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Bureaucrat &			Bureaucrat::operator=( Bureaucrat const & other )
{
	if (other._grade < 1)
		throw GradeTooHighException();
	else if (other._grade > 150)
		throw GradeTooLowException();
	_grade = other._grade;
	return *this;
}

std::ostream &			operator<<( std::ostream & ostream, Bureaucrat &obj)
{
	ostream << obj.getName() << ", bureaucrat grade " << obj.getGrade() << '\n';
	return ostream;
}


/*
** --------------------------------- METHODS ----------------------------------
*/

void		Bureaucrat::increaseGrade( void ) throw(GradeTooHighException)
{
	if (_grade == 1)
		throw GradeTooHighException();
	else
		_grade--;
}

void		Bureaucrat::decreaseGrade( void ) throw(GradeTooLowException)
{
	if (_grade == 150)
		throw GradeTooLowException();
	else
		_grade++;
}

void		Bureaucrat::signForm( Form &form )
{
	try
	{
		form.beSigned(*this);
	}
	catch (const Form::GradeTooLowException& e)
	{
		std::cout << _name << " cannot sign " << form.getName() << " because his grade is lower than the form's\n";
	}
	if (form.isSigned())
		std::cout << _name << " signs " << form.getName() << '\n';
}

void		Bureaucrat::executeForm( Form &form )
{
	try
	{
		form.execute(*this);
		std::cout << this->getName() << " executes " << form.getName() << '\n';
	}
	catch (const Form::NotSignedException &e)
	{
		std::cout << _name << " cannot execute " << form.getName() << " because is not signed\n";
	}
	catch (const Form::GradeTooLowException &e)
	{
		std::cout << this->getName() << " doesn't have enough grade to execute " << form.getName() << '\n';
	}
}

/*
**								CUSTOM EXCEPTIONS
*/

const char*		Bureaucrat::GradeTooHighException::what() const throw()
{
	return ("Grade was set to a value too high");
}

const char*		Bureaucrat::GradeTooLowException::what() const throw()
{
	return ("Grade was set to a value too low");
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

std::string	Bureaucrat::getName( void ) const
{
	return (_name);
}

int			Bureaucrat::getGrade( void ) const
{
	return (_grade);
}

/* ************************************************************************** */