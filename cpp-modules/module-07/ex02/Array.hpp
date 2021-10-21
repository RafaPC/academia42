#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <exception>

template <class T>
class Array
{
	T	*_elements;
	int	_length;

	public:
		Array( void )
		{
			_elements = new T[0];
			_length = 0;
		}

		Array( unsigned int n)
		{
			_elements = new T[n];
			_length = n;
		}

		Array( const Array &other)
		{
			*this = other;
		}

		~Array()
		{
			delete[] _elements;
		}

		int	size( void ) const
		{
			return (_length);
		}

		T	&operator [](int i)
		{
			if (i < 0 || i >= _length)
				throw std::out_of_range("index out of range");
			else
				return (_elements[i]);
		}

		T	operator [](int i) const
		{
			if (i < 0 || i >= _length)
				throw std::out_of_range("index out of range");
			else
				return (_elements[i]);
		}

		void	operator =(const Array &other)
		{
			_length = other._length;
			delete[] _elements;
			_elements = new T[_length];
			for (int i = 0; i < _length; i++)
				_elements[i] = other._elements[i];
		}
};

#endif