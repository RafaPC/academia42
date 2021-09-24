#ifndef CURE_HPP
# define CURE_HPP

# include <string>
# include "AMateria.hpp"
# include "ICharacter.hpp"

class Cure: public AMateria
{

	public:

		Cure();
		Cure( Cure const & );
		~Cure();

		Cure &		operator=( Cure const & );
		AMateria*	clone() const;
		void		use(ICharacter& target);
	private:

};

#endif /* ************************************************************ CURE_H */