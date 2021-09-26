#ifndef BRAIN_HPP
# define BRAIN_HPP

# include <iostream>
# include <string>

class Brain
{

	public:
		std::string	ideas[100];
		Brain( void );
		Brain( Brain const & src );
		~Brain();
		Brain&		operator=( Brain const &brain );
};

#endif /* *********************************************************** BRAIN_H */