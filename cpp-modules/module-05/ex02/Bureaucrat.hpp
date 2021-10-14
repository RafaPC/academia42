#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

# include <iostream>
# include <string>
# include <exception>

class Form;

# include "Form.hpp"

class Bureaucrat
{
	private:
		const std::string	_name;
		int					_grade;

	public:

		Bureaucrat( std::string name = "Unnamed", int grade = 150);
		Bureaucrat( Bureaucrat const & src );
		~Bureaucrat();

		Bureaucrat &		operator=( Bureaucrat const & rhs );
		std::string			getName( void ) const;
		int					getGrade( void ) const;
		void				signForm( Form &form );
		void				executeForm( Form &form );

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

	void				increaseGrade( void ) throw(GradeTooHighException);
	void				decreaseGrade( void ) throw(GradeTooLowException);
};

std::ostream &		operator<<( std::ostream &ostream, Bureaucrat &obj );

#endif /* ****************************************************** BUREAUCRAT_H */