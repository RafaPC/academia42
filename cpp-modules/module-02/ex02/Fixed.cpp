#include <iostream>
#include <cmath>
#include "Fixed.hpp"


// CONSTRUCTORS

Fixed::Fixed()
{
	// std::cout << "Default constructor called\n";
	this->value = 0;
}

Fixed::Fixed ( const int integer_value )
{
	// std::cout << "Int constructor called\n";
	this->value = integer_value << fractional_bits;
	if (integer_value < 0)
	{
		for (int bit_index = 31; bit_index >= 32 - fractional_bits; bit_index--)
			this->value |= 1U << bit_index;
	}
}

Fixed::Fixed( const float float_value )
{
	std::cout << "Float constructor called\n";
	float	rounded_value = std::roundf(float_value);
	// roundf rounds up from 0.5, here I fix it
	if (float_value > 0.0f && rounded_value > float_value)
		rounded_value -= 1.0f;
	else if (float_value < 0.0f && rounded_value < float_value)
		rounded_value += 1.0f;

	rounded_value = (rounded_value < 0) ? -rounded_value : rounded_value;	
	this->value = (int)rounded_value << fractional_bits;

	float	divider = 2.0f;
	float	point_value = float_value - rounded_value;
	float	acummulator = 0.0f;
	for (int bit_index = fractional_bits - 1; bit_index >= 0; bit_index--, divider *= 2.0f)
	{
		if (acummulator + 1.0f/divider <= point_value)
		{
			this->value |= 1UL << bit_index;
			acummulator += 1.0f/divider;
		}
		else if (bit_index > 0)
		{
			// this will represent the total accumulated value if all bits from the next were set to 1
			float	acummulator_aux = acummulator;
			float	divider_copy = divider * 2;
			for (int i = bit_index - 1; i >= 0; i--, divider_copy *= 2.0f)
				acummulator_aux += + 1.0f/divider_copy;
			// if there's less difference when the value is bigger than when the value is smaller
			// the bigger one is used
			if (acummulator + 1.0f/divider - point_value < point_value - acummulator_aux)
			{
				this->value |= 1UL << bit_index;
				acummulator += 1.0f/divider;
				break ; // it breaks out of the loop because now it already exceeds the value
			}
		}
		else if (acummulator + 1.0f/256 - point_value < point_value - acummulator)
		{
			this->value |= 1UL;
			acummulator += 1.0f/256;
		}
	}
}

Fixed::Fixed( const Fixed& fixed_obj)
{
	// std::cout << "Copy constructor called\n";
	*this = fixed_obj;
}

Fixed::~Fixed()
{
	// std::cout << "Destructor called\n";
}

//PUBLIC METHODS 
int				Fixed::getRawBits( void ) const
{
	// std::cout << "getRawBits member funcion called\n";
	return (this->value);
}

void			Fixed::setRawBits( int const raw )
{
	this->value = raw;
}

float			Fixed::toFloat( void ) const
{
	float	float_value = (float)this->toInt();
	float	divider = 2.0f;
	for (int i = fractional_bits - 1; i >= 0; i--, divider *= 2.0)
	{
		if ((this->value >> i) & 1U && float_value >= 0)
			float_value += 1.0f/divider;
		else if ((this->value >> i) & 1U && float_value < 0)
			float_value -= 1.0f/divider;
	}
	return (float_value);
}

int				Fixed::toInt( void ) const
{
	//aquí checkear el tema de los negativos y eso
	int	integer_value = this->value >> fractional_bits;
	// checks the first bit of the stored value
	if ((this->value >> 31) & 1U)
	{
		for (int i = 31; i >= 32 - fractional_bits; i--)
			integer_value |= 1UL << i;
	}
	return (integer_value);
}

//	OVERLOADS

//		ASSIGNATION
void			Fixed::operator =( const Fixed &fixed_obj )
{
	// std::cout << "Assignation operator called\n";
	this->value = fixed_obj.value;
}

//		OUTPUT STREAM
std::ostream&	operator <<( std::ostream& stream, const Fixed& fixed )
{
	stream << fixed.toFloat();
	return (stream);
}

//		ARITHMETIC OPERATORS
Fixed			operator +(const Fixed &fixed1, const Fixed &fixed2)
{
	return (Fixed(fixed1.toFloat() + fixed2.toFloat()));
}

Fixed			operator -(const Fixed &fixed1, const Fixed &fixed2)
{
	return (Fixed(fixed1.toFloat() - fixed2.toFloat()));
}

Fixed			operator *(const Fixed &fixed1, const Fixed &fixed2)
{
	return (Fixed(fixed1.toFloat() * fixed2.toFloat()));
}

Fixed			operator /(const Fixed &fixed1, const Fixed &fixed2)
{
	return (Fixed(fixed1.toFloat() / fixed2.toFloat()));
}

Fixed			operator ++(Fixed &fixed)
{
	fixed.setRawBits(fixed.getRawBits() + 1);
	return (fixed);
}

Fixed			operator ++(Fixed &fixed, int)
{
	Fixed fixed_copy;
	fixed_copy.setRawBits(fixed.getRawBits());
	fixed.setRawBits(fixed.getRawBits() + 1);
	return (fixed_copy);
}

Fixed			operator --(Fixed &fixed)
{
	fixed.setRawBits(fixed.getRawBits() - 1);
	return (fixed);
}

Fixed			operator--(Fixed &fixed, int)
{
	Fixed fixed_copy;
	fixed_copy.setRawBits(fixed.getRawBits());
	fixed.setRawBits(fixed.getRawBits() - 1);
	return (fixed_copy);
}

//		COMPARISON OPERATORS
bool			Fixed::operator ==(const Fixed &fixed) const
{
	if (this->toInt() == fixed.toInt() && this->toFloat() == fixed.toFloat())
		return (true);
	else
		return (false);
}

bool			Fixed::operator !=(const Fixed &fixed) const
{
	return (!(*this == fixed));
}

bool			Fixed::operator <(const Fixed &fixed) const
{
	if (this->toInt() < fixed.toInt() || this->toFloat() < fixed.toFloat())
		return (true);
	else
		return (false);
}

bool			Fixed::operator >(const Fixed &fixed) const
{
	if (this->toInt() > fixed.toInt() || this->toFloat() > fixed.toFloat())
		return (true);
	else
		return (false);
}

bool			Fixed::operator <=(const Fixed &fixed) const
{
	return ((*this < fixed || *this == fixed) ? true : false);
}

bool			Fixed::operator >=(const Fixed &fixed) const
{
	return ((*this > fixed || *this == fixed) ? true : false);
}

// STATIC METHODS

Fixed&			Fixed::max(Fixed &fixed1, Fixed &fixed2)
{
	return (fixed1 >= fixed2 ? fixed1 : fixed2);
}

const Fixed&	Fixed::max(const Fixed &fixed1, const Fixed &fixed2)
{
	return (fixed1 >= fixed2 ? fixed1 : fixed2);
}

Fixed&			Fixed::min(Fixed &fixed1, Fixed &fixed2)
{
	return (fixed1 <= fixed2 ? fixed1 : fixed2);
}

const Fixed&	Fixed::min(const Fixed &fixed1, const Fixed &fixed2)
{
	return (fixed1 <= fixed2 ? fixed1 : fixed2);
}
