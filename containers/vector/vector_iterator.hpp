#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP
#include <iterator>
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

				VectorIterator() {}
				// VectorIterator(int n) { _pointer = n; } //FIXME:
				VectorIterator(pointer ptr) : _pointer(ptr) {}
			VectorIterator &operator=(const VectorIterator &other)
			{
				_pointer = other._pointer;
				return (*this);
			};
			//FIXME:
			// VectorIterator &operator=(const pointer &other)
			// {
			// 	_pointer = other;
			// 	return (*this);
			// };

			
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
				VectorIterator tmp(this->_pointer);
				++_pointer;
				return (tmp);
			}
			VectorIterator &operator--()
			{
				--_pointer;
				return (*this);
			}
			VectorIterator operator--(int)
			{
				VectorIterator tmp(this->_pointer);
				--_pointer;
				return (tmp);
			}
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
			VectorIterator operator+(int n) const
			{
				VectorIterator aux(*this);
				aux += n;
				return (aux);
			}
			VectorIterator operator-(pointer n) const
			{
				VectorIterator aux(*this);
				this->_pointer = this->_pointer - n;
				return (aux);
			}
			difference_type operator-(VectorIterator<T> n) const
			{
				// VectorIterator<T> aux(*this);
				// aux._pointer = reinterpret_cast<pointer>(aux._pointer - n._pointer);
				return (reinterpret_cast<difference_type>(this->_pointer - n._pointer));
			}
			//FIXME: *it = *(it - 1);
			VectorIterator operator-(int n) const
			{
				VectorIterator aux;
				aux._pointer = this->_pointer - n;
				return (aux);
			}

			VectorIterator &operator+=(int n)
			{
				this->_pointer += n;
				return (*this);
			}
			VectorIterator &operator-=(int n)
			{
				this->_pointer -= n;
				return (*this);
			}
			//TODO:
			// VectorIterator &operator-=(VectorIterator n)
			// {
			// 	this->_pointer = this->_pointer - n._pointer;
			// 	return (*this);
			// }
			value_type &operator[](int n)
			{
				return (*(this->_pointer + n));
			}
			value_type operator[](int n) const
			{
				return (*(this->_pointer + n));
			}

			private:
				pointer	_pointer;
		};
};

#endif