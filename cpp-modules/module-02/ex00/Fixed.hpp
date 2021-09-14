#ifndef FIXED_HPP
# define FIXED_HPP

class Fixed
{
private:

	int	value;
	static const int fractional_bits = 8;

public:
	Fixed( void );
	Fixed( Fixed& obj);
	~Fixed();
	int		getRawBits( void ) const;
	void	setRawBits( int const raw );
	void	operator = ( const Fixed &fixed );
};

#endif