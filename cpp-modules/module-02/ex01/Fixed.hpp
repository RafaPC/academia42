#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>

class Fixed
{
private:

	int	value;
	static const int fractional_bits = 8;

public:
	Fixed ( void );
	Fixed ( const int integer_value );
	Fixed ( const float float_value );
	Fixed ( const Fixed& fixed );
	~Fixed();

	int		getRawBits( void ) const;
	void	setRawBits( int const raw );
	void	operator =( const Fixed &fixed );
	float	toFloat( void ) const;
	int		toInt( void ) const;
};
std::ostream&	operator <<( std::ostream& stream, const Fixed& fixed );

#endif