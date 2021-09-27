#ifndef CHARACTER_HPP
# define CHARACTER_HPP

# include <string>
# include "ICharacter.hpp"

class Character: public ICharacter
{

	public:
		Character( void );
		Character( std::string name);
		Character( Character const & src );
		~Character();

		Character &		operator=( Character const & rhs );
		std::string const & getName() const;
		void equip( AMateria* m );
		void unequip( int idx );
		void use( int idx, ICharacter& target );

	private:
		int	_learned_materias_length;
};

#endif /* ******************************************************* CHARACTER_H */