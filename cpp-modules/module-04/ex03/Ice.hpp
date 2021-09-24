#ifndef ICE_HPP
# define ICE_HPP

# include <string>
# include "AMateria.hpp"

class Ice: public AMateria
{

	public:

		Ice();
		Ice( Ice const & );
		~Ice();

		Ice &		operator=( Ice const & );
		AMateria*	clone() const;
		void		use(ICharacter& target);
};

#endif /* ************************************************************* ICE_H */