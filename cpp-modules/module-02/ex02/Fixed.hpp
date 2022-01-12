#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>

class Fixed
{
private:

	int	value;
	static const int fractional_bits = 8;

public:
	Fixed( void );
	Fixed ( const int integer_value );
	Fixed( const float float_value );
	Fixed( const Fixed& obj);
	~Fixed();

	int		getRawBits( void ) const;
	void	setRawBits( int const raw );
	void	operator = (const Fixed &fixed);
	float	toFloat( void ) const;
	int		toInt( void ) const;

	//Comparison operators overloads
	bool	operator ==(const Fixed &fixed) const;
	bool	operator !=(const Fixed &fixed) const;
	bool	operator <(const Fixed &fixed) const;
	bool	operator >(const Fixed &fixed) const;
	bool	operator <=(const Fixed &fixed) const;
	bool	operator >=(const Fixed &fixed) const;

	//Arithmetic operators overloads
	//STATIC
	static Fixed&		max(Fixed &fixed1, Fixed &fixed2);
	static Fixed&		min(Fixed &fixed1, Fixed &fixed2);
	static const Fixed&	max(const Fixed &fixed1, const Fixed &fixed2);
	static const Fixed&	min(const Fixed &fixed1, const Fixed &fixed2);
};
Fixed			operator +(const Fixed &fixed1, const Fixed &fixed2);
Fixed			operator -(const Fixed &fixed1, const Fixed &fixed2);
Fixed			operator *(const Fixed &fixed1, const Fixed &fixed2);
Fixed			operator /(const Fixed &fixed1, const Fixed &fixed2);
Fixed			operator ++(Fixed &fixed1);
Fixed			operator ++(Fixed &fixed1, int);
Fixed			operator --(Fixed &fixed1);
Fixed			operator --(Fixed &fixed1, int);
std::ostream&	operator <<(std::ostream& stream, const Fixed& fixed);

#endif