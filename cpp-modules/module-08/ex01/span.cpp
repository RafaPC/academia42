#include "span.hpp"
#include <exception>
#include <algorithm>
#include <iostream>
#include <stdlib.h>

Span::Span( void ): _max_size(0), _size(0)
{
	_elements = std::vector<int>(0);
}

Span::Span( unsigned int length ) : _max_size(length), _size(0)
{
	_elements = std::vector<int>(length);
}

Span::Span( Span &other )
{
	*this = other;
}

Span	&Span::operator =(const Span &other)
{
	_max_size = other._max_size;
	_size = other._size;
	_elements = other._elements;
	return (*this);
}

void	Span::addNumber( int number )
{
	if (_size < _max_size)
	{
		_elements[_size] = number;
		_size++;
	}
	else
		throw std::length_error("span already full");
}

void	Span::randomFill( std::vector<int>::iterator begin, std::vector<int>::iterator end )
{
	if (begin < _elements.begin() || begin >= _elements.end())
		throw std::length_error("begin iterator is out of range");
	else if (end <= _elements.begin() || end > _elements.end())
		throw std::length_error("end iterator is out of range");
	else if (end - begin > _size)
		_size = end - begin;
	srand(time(NULL));
	std::generate(begin, end, rand);
}

int	Span::shortestSpan( void ) const
{
	if (_size <= 1)
		throw std::length_error("span must have at least two numbers");

	// creates copy of vector
	std::vector<int>	copy_vector(_elements);
	// sorts new vector
	std::sort(copy_vector.begin(), copy_vector.end());
	// gets iterator of new vector
	std::vector<int>::const_iterator it = copy_vector.begin();
	int	span = abs(it[0] - it[1]);
	++it;
	while (it < copy_vector.end())
	{
		const int new_span = abs(it[0] - it[1]);
		if (new_span < span)
			span = new_span;
		++it;
	}
	return (span);
}

int	Span::longestSpan( void ) const
{
	if (_elements.size() <= 1)
		throw std::length_error("span must have at least two numbers");

	std::vector<int>::const_iterator min_elem = std::min_element(_elements.begin(), _elements.end());
	std::vector<int>::const_iterator max_elem = std::max_element(_elements.begin(), _elements.end());
	return (*max_elem - *min_elem);
}
