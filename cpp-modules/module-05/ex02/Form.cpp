#include "Form.hpp"
#include "Bureaucrat.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Form::Form( std::string name, int sign_grade, int execute_grade, std::string target ):_name(name),
_sign_grade(sign_grade), _execute_grade(execute_grade), _is_signed(false), _target(target)
{
	if (sign_grade > 150 || execute_grade > 150)
		throw Form::GradeTooLowException();
	else if (sign_grade < 1 || execute_grade < 1)
		throw Form::GradeTooHighException();
}

Form::Form( const Form & form ):
_name(form._name), _sign_grade(form._sign_grade),
_execute_grade(form._execute_grade), _is_signed(form._is_signed), _target(form._target)
{
	if (_sign_grade > 150 || _execute_grade > 150)
		throw Form::GradeTooLowException();
	else if (_sign_grade < 1 || _execute_grade < 1)
		throw Form::GradeTooHighException();
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Form::~Form()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Form &				Form::operator=( Form const & form )
{
	(void)form;
	return *this;
}

std::ostream &			operator<<( std::ostream & ostream, Form & form )
{
	ostream << "Form name: " << form.getName() << "\nMinimum grade required: " << form.getSignGrade() << ""
	"\nSigned: " << (form.isSigned() ? "Yes\n" : "No\n");
	return ostream;
}


/*
** --------------------------------- METHODS ----------------------------------
*/

void		Form::beSigned(Bureaucrat &bureaucrat) throw(Form::GradeTooLowException)
{
	if (bureaucrat.getGrade() > _sign_grade)
		throw Form::GradeTooLowException();
	else
		_is_signed = true;
}

void				Form::execute(Bureaucrat const & executor) const
{
	if (!_is_signed)
		throw Form::NotSignedException();
	if (executor.getGrade() > _execute_grade)
		throw Form::GradeTooLowException();
	else if (!_is_signed)
		std::cout << "Error: Form's not signed\n";
	else
		executeAction();

}

/*
**								CUSTOM EXCEPTIONS
*/

const char*		Form::GradeTooHighException::what() const throw()
{
	return ("Form's grade is too high");
}

const char*		Form::GradeTooLowException::what() const throw()
{
	return ("Form's grade is too low");
}

const char*		Form::NotSignedException::what() const throw()
{
	return ("Form is not signed");
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

const std::string	Form::getName( void ) const
{
	return (_name);
}

bool	Form::isSigned( void ) const
{
	return (_is_signed);
}

int	Form::getSignGrade( void ) const
{
	return (_sign_grade);
}

int	Form::getExecuteGrade( void ) const
{
	return (_execute_grade);
}

const std::string&	Form::getTarget( void ) const
{
	return (_target);
}

/* ************************************************************************** */