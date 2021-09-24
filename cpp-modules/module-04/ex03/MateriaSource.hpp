#ifndef MATERIASOURCE_HPP
# define MATERIASOURCE_HPP

# include <string>
# include "IMateriaSource.hpp"
# include "AMateria.hpp"

class MateriaSource: public IMateriaSource
{

	public:

		MateriaSource();
		MateriaSource( MateriaSource const &src );
		~MateriaSource();

		void		learnMateria( AMateria* );
		AMateria*	createMateria( std::string const & type );
		MateriaSource&		operator=( MateriaSource const &rhs );

	private:
		AMateria	*_learned_materias[4];
		int			_learned_materias_length;
};

#endif /* *************************************************** MATERIASOURCE_H */