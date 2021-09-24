#ifndef AMATERIA_HPP
# define AMATERIA_HPP

# include <string>
# include "ICharacter.hpp"
class ICharacter;

class AMateria
{
	protected:
		std::string	type;

	public:
		AMateria( std::string const &type );
		AMateria();
		AMateria( AMateria const & src );
		virtual ~AMateria();

		std::string const	&getType() const; //Returns the materia type
		virtual AMateria*	clone() const = 0;
		virtual void		use( ICharacter& target );
		AMateria &			operator=( AMateria const & rhs );
};

#endif /* ******************************************************** AMATERIA_H */