#ifndef ICHARACTER_HPP
# define ICHARACTER_HPP

# include <string>
# include "AMateria.hpp"
class AMateria;

# define MAX_LEARNED_MATERIA_CAPACITY 4

class ICharacter
{
	protected:
		std::string	name;
		AMateria	*inventory[MAX_LEARNED_MATERIA_CAPACITY];
	public:
		virtual ~ICharacter() {}
		virtual std::string const & getName() const = 0;
		virtual void equip( AMateria* m ) = 0;
		virtual void unequip( int idx ) = 0;
		virtual void use( int idx, ICharacter& target ) = 0;
};

#endif /* ****************************************************** ICHARACTER_H */