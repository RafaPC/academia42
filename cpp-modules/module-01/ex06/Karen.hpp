#ifndef KAREN_HPP
# define KAREN_HPP

#include <string>

class Karen
{
private:
	void		debug( void );
	void		info( void );
	void		warning( void );
	void		error( void );
	void		(Karen::*function_ptrs[4])();
	std::string	modes[4];

public:
	Karen( void );
	void	complain ( std::string level );
	void	filter( std::string mode );
};

#endif