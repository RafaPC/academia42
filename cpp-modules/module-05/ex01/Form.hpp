#ifndef FORM_HPP
# define FORM_HPP

# include <iostream>
# include <string>

class Bureaucrat;

# include "Bureaucrat.hpp"

class Form
{

	public:

		class GradeTooHighException: public std::exception
		{
			public:
				const char* what() const throw();
		};

		class GradeTooLowException: public std::exception
		{
			public:
				const char* what() const throw();
		};

		Form(std::string name = "Standard form", int sign_grade = 150, int execute_grade = 150);
		Form( Form const & src );
		~Form();

		Form &				operator=( Form const & rhs );
		void				beSigned(Bureaucrat &bureaucrat) throw(Form::GradeTooLowException);
		const std::string	getName( void ) const;
		bool				isSigned( void ) const;
		int					getSignGrade( void ) const;
		int					getExecuteGrade( void ) const;

	private:
		const std::string	_name;
		const int			_sign_grade;
		const int			_execute_grade;
		bool				_is_signed;
};

std::ostream &			operator<<( std::ostream & ostream, Form & form );

#endif /* ************************************************************ FORM_H */