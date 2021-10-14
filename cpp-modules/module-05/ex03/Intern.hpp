#ifndef INTERN_HPP
# define INTERN_HPP

# include <iostream>
# include <string>
# include "Form.hpp"

class Intern
{

	public:

		Intern();
		Intern( Intern const & src );
		~Intern();

		Intern &		operator=( Intern const & rhs );
		Form*			makeForm( std::string name, std::string target);
	private:
		Form	*makeShrubbdery( std::string target );
		Form	*makeRobot( std::string target );
		Form	*makePresidential( std::string target );
};

#endif /* ********************************************************** INTERN_H */