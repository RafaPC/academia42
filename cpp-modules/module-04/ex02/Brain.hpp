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
		std::string	getIdea( void ) const;
		void		changeIdea( const std::string );
	private:

};

#endif /* *********************************************************** BRAIN_H */