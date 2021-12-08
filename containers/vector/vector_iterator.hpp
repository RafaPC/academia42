#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

#include "utils.hpp"

namespace ft
{

	template< typename T >
		class VectorIterator
		{
			public:
				typedef std::random_access_iterator_tag		iterator_category;
				typedef std::ptrdiff_t						difference_type;
				typedef T									value_type;
				typedef T*									pointer;
				typedef T&									reference;

				VectorIterator(void) : _pointer(NULL) {}
				VectorIterator(pointer ptr) : _pointer(ptr) {}
				VectorIterator(VectorIterator const &other) : _pointer(other._pointer) {}
				VectorIterator &operator=(const VectorIterator &other)
				{
					_pointer = other._pointer;
					return (*this);
				};
				// conversion operator to const VectorIterator
				// just constructs a VectorIterator of const T
				operator	VectorIterator<const T>(void) const
				{
					return (VectorIterator<const T>(_pointer));
				}
			reference operator*() const
			{
				return (*_pointer);
			}
			pointer operator->() const
			{
				return (_pointer);
			}
			VectorIterator &operator++()
			{
				++_pointer;
				return (*this);
			}
			VectorIterator operator++(int)
			{
				VectorIterator temp(_pointer);
				++_pointer;
				return (temp);
			}
			VectorIterator &operator--()
			{
				--_pointer;
				return (*this);
			}
			VectorIterator operator--(int)
			{
				VectorIterator temp(_pointer);
				--_pointer;
				return (temp);
			}
			
			// RELATIONAL OPERATORS
			bool operator== (const VectorIterator &x) const
			{
				return (_pointer == x._pointer);
			}
			bool operator!= (const VectorIterator &x) const
			{
				return (_pointer != x._pointer);
			}
			bool operator> (const VectorIterator &x) const
			{
				return (_pointer > x._pointer);
			}
			bool operator>= (const VectorIterator &x) const
			{
				return (_pointer >= x._pointer);
			}
			bool operator< (const VectorIterator &x) const
			{
				return (_pointer < x._pointer);
			}
			bool operator<= (const VectorIterator &x) const
			{
				return (_pointer <= x._pointer);
			}
			
			// ARITHMETIC OPERATIONS
			VectorIterator operator+(difference_type n) const
			{
				return (VectorIterator(_pointer + n));
			}

			VectorIterator &operator+=(difference_type n)
			{
				_pointer += n;
				return (*this);
			}

			difference_type operator-(VectorIterator<T> n) const
			{
				return (reinterpret_cast<difference_type>(_pointer - n._pointer));
			}
			
			VectorIterator operator-(difference_type n) const
			{
				return (VectorIterator(_pointer - n));
			}

			VectorIterator &operator-=(difference_type n)
			{
				_pointer -= n;
				return (*this);
			}

			// OFFSET DEFERENCE OPERATOR
			value_type &operator[](difference_type n)
			{
				return (*(_pointer + n));
			}

			value_type operator[](difference_type n) const
			{
				return (*(_pointer + n));
			}

			private:
				pointer	_pointer;
		};
};

#endif