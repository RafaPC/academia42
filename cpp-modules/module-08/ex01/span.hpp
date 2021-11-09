#ifndef SPAN_HPP
# define SPAN_HPP
# include <vector>

class Span
{
	public:
		std::vector<int>	_elements;
		Span( void );
		Span( unsigned int size );
		Span( Span &other );
		void	addNumber( int number );
		void	randomFill( std::vector<int>::iterator begin, std::vector<int>::iterator end );
		int		shortestSpan( void ) const;
		int		longestSpan( void ) const;
		Span	&operator =(const Span &other);
	private:
		unsigned int	_max_size;
		unsigned int	_size;
};

#endif