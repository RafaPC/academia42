#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include <iterator>
#include <limits>
#include <cstdlib>
#include <exception>
#include <memory>
#include <iostream>
#include <sstream> // std::stringstream for out_of_range message
#include "vector_iterator.hpp"
#include "utils.hpp"

//TODO: checkear cuando dejo como elementos después de acabar el size y antes de acabarse de verdad el vector
// creo que no hay problema porque suelen ser elementos que tienen su copia en otro lado antes del size
// pero puede que dejar elementos despues del size esté mal y tenga que destruirlos siempre
namespace ft {

template < class T, class Allocator = std::allocator<T> >
class vector
{
	public:
		typedef T												value_type;
		typedef Allocator										allocator_type;
		typedef typename allocator_type::pointer				pointer;
		typedef typename allocator_type::const_pointer			const_pointer;
		typedef typename allocator_type::reference				reference;
		typedef typename allocator_type::const_reference		const_reference;
		typedef VectorIterator<value_type>						iterator;
		typedef VectorIterator<const value_type>				const_iterator;
		typedef ft::reverse_iterator<iterator>					reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
		typedef size_t											size_type;
		typedef std::ptrdiff_t									difference_type;

	private:
		T			*_data;
		size_type	_size;
		size_type	_capacity;
		Allocator	_allocator;

		void	_range_check(size_type n) const
		{
			if (n >= _size)
			{
				std::stringstream exception_message;
				exception_message << "vector::_range_check: n (which is " << n << ""
				") >= this->size() (which is " << _size << ")";
				throw std::out_of_range(exception_message.str());
			}
		}

		void	_shift_elements(size_type until_index, size_type shift_length)
		{
			for (size_type i = _size - 1; i >= until_index; --i)
				_data[i] = _data[i - shift_length];
		}

	public:

		//	CONSTRUCTORS
		explicit vector (const allocator_type& alloc = allocator_type())
		: _data(NULL), _size(0), _capacity(0), _allocator(alloc) { }

		explicit vector (size_type n, const value_type& val = value_type(),
			const allocator_type& alloc = allocator_type())
			: _size(n), _capacity(n), _allocator(alloc)
			{
				_data = _allocator.allocate(n);
				while (n--)
					_allocator.construct(&_data[n], val);
			}
		
		template <typename InputIterator>
		vector (InputIterator first, InputIterator last,
			const allocator_type& alloc = allocator_type(),
			typename enable_if<is_convertible<typename InputIterator::iterator_category, std::input_iterator_tag>::value, void>::type* = NULL)
			: _size(std::distance(first, last)), _capacity(_size), _allocator(alloc)
			{
				_data = _allocator.allocate(_capacity);
				for (size_type i = 0; first != last; ++i, ++first)
					_allocator.construct(_data + i, *first);
			}
		vector (const vector& x)
		{
			_data = NULL;
			*this = x;
		}

		//	DESTRUCTOR
		~vector()
		{
			for (size_type i = 0; i < _size; ++i)
				_allocator.destroy(&_data[i]);
			_allocator.deallocate(_data, _capacity);
		}

		vector& operator= (const vector& x)
		{
			if (_data == NULL)
				_data = _allocator.allocate(x._capacity, x._data);
			else
			{
				for (size_type i = 0; i < _size; ++i)
					_allocator.destroy(&_data[i]);
				if (_capacity < x._size)
				{
					pointer	aux_data = _allocator.allocate(x._size, _data);
					_allocator.deallocate(_data, _capacity);
					_data = aux_data;
				}
			}
			_capacity = x._size;
			_size = x._size;
			for (size_type i = 0; i < _size; ++i)
				_allocator.construct(&_data[i], x._data[i]);
			return (*this);
		}

		// ITERATORS
		iterator				begin()
		{
			return (iterator(_data));
		}
		
		const_iterator			begin() const
		{
			return (const_iterator(_data));
		}
		
		iterator				end()
		{
			return (iterator(&_data[_size]));
		}
		
		const_iterator			end() const
		{
			return (iterator(&_data[_size]));
		}
		
		reverse_iterator		rbegin()
		{
			return (reverse_iterator(&_data[_size]));
		}
		
		const_reverse_iterator	rbegin() const
		{
			return (const_reverse_iterator(&_data[_size]));
		}
		
		reverse_iterator		rend()
		{
			return (reverse_iterator(_data));
		}
		
		const_reverse_iterator	rend() const
		{
			return (const_reverse_iterator(_data));
		}

		// CAPACITY
		size_type	size() const
		{
			return (_size);
		}
		
		size_type	max_size() const
		{
			return (std::numeric_limits<size_type>::max() / sizeof(value_type));
		}
		
		size_type	capacity() const
		{
			return (this->_capacity);
		}
		
		void		resize(size_type new_size, value_type val = value_type())
		{
			while (new_size > _size)
				pop_back();
			while (new_size > _size)
				push_back(val);
			if (new_size > _capacity)
				reserve(new_size);
		}
		
		bool		empty() const
		{
			return (_size == 0);
		}
		
		void		reserve(size_type new_capacity)
		{
			if (new_capacity > max_size())
			{
				std::stringstream exception_message;
				exception_message << "vector::reserve: new_capacity (" << new_capacity << ""
				") requested is greater than maximum capacity (" << max_size() << ")";
				throw std::length_error(exception_message.str());
			}
			else if (new_capacity > _capacity)
			{
				pointer new_data = _allocator.allocate(new_capacity, _data);
				for (size_type i = 0; i < _size; ++i)
				{
					_allocator.construct(&new_data[i], _data[i]);
					_allocator.destroy(&_data[i]);
				}
				_allocator.deallocate(_data, _capacity);
				_data = new_data;
				_capacity = new_capacity;
			}
		}

		// ELEMENT ACCESS
		
		reference 		operator[] (size_type n)
		{
			return (_data[n]);
		}
		
		const_reference operator[] (size_type n) const
		{
			return (_data[n]);
		}
		
		reference 		at (size_type n)
		{
			_range_check(n);
			return (_data[n]);
		}
		
		const_reference at (size_type n) const
		{
			_range_check(n);
			return (_data[n]);
		}
		
		reference 		front()
		{
			return (_data[0]);
		}
		
		const_reference front() const
		{
			return (_data[0]);
		}
		
		reference 		back()
		{
			return (_data[_size - 1]);
		}
		
		const_reference back() const
		{
			return (this->_data[this->_size - 1]);
		}

		// TODO: if InputIterator is not at least of a forward iterator category 
		// (i.e., it is just an input iterator) the new capacity cannot be determined
		// beforehand and the operation incurs in additional logarithmic complexity
		// in the new size (reallocations while growing).
		template <class InputIterator>
			void	assign(InputIterator first, InputIterator last,
			typename enable_if<is_convertible<typename InputIterator::iterator_category, std::input_iterator_tag>::value, void>::type* = NULL)
			{
				const size_type	new_size = std::distance(first, last);
				clear();
				reserve(new_size);
				_size = new_size;
				for (size_type i = 0; first != last; ++i, ++first)
					_allocator.construct(&_data[i], *first);
			}

		void assign (size_type n, const value_type& val)
		{
			reserve(n);
			_size = n;
			while (--n)
				_allocator.construct(&_data[n], val);
		}

		void push_back (const value_type& val)
		{
			reserve(++_size);
			_allocator.construct(&_data[_size - 1], val);
		}

		void pop_back()
		{
			_allocator.destroy(&_data[--_size]);
		}

		//TODO: con insertes y asignes, checkear que si la posicion es el primer elemento
		// no haga cosas raras con el 0, tipo _data[0] = _data[0 - 1]
		iterator	insert (iterator position, const value_type& val)
		{
			const size_type position_index = std::distance(begin(), position);
			reserve(++_size);
			// it sets each position value by its previous one from end to the position
			// of the inserted element
			_shift_elements(position_index + 1, 1);

			_allocator.construct(&_data[position_index], val);
			return (&_data[position_index]);
		}

		void	insert (iterator position, size_type n, const value_type& val)
		{
			if (n == 0)
				return;
			const size_type distance = std::distance(begin(), position);
			reserve(_size + n);
			_size += n;

			_shift_elements(distance + n, n);
			for (size_type i = 0; i < n; ++i)
				_allocator.construct(&_data[distance + i], val);
		}

		// TODO: Additionally, if InputIterator in the range insert (3) is not at least of a forward
		// iterator category (i.e., just an input iterator) the new capacity cannot be determined 
		// beforehand and the insertion incurs in additional logarithmic complexity in size (reallocations).
		template <class InputIterator>
		void	insert (iterator position, InputIterator first, InputIterator last,
		typename enable_if<is_convertible<typename InputIterator::iterator_category, std::input_iterator_tag>::value, void>::type* = NULL)
		{
			const size_type		new_elements_size = std::distance(first, last);
			if (new_elements_size == 0)
				return;
			size_type			insert_index = std::distance(begin(), position);

			reserve(_size + new_elements_size);
			_size += new_elements_size;
			// Elements from position are moved new_elements_size to the right
			// in reverse order so that no elements are removed
			_shift_elements(insert_index + new_elements_size, new_elements_size);
			// New elements are inserted
			for (; first != last; ++insert_index, ++first)
				_allocator.construct(&_data[insert_index], *first);
		};

		iterator erase (iterator position)
		{
			size_type	position_index = std::distance(begin(), position);
			_allocator.destroy(&_data[position_index]);
			--_size;
			if (position != end())
			{
				for (size_type i = position_index + 1; i < _size; ++i)
					_data[i - 1] = _data[i];
			}
			return (position);
		}

		// TODO: chequiar lo del deference iterator as rvalue y eso
		iterator erase (iterator first, iterator last)
		{
			const size_type	distance = std::distance(first, last);
			_size -= distance;

			iterator		it = first;
			iterator		end = this->end();
			while (it != last)
			{
				_allocator.destroy(&*it);
				++it;
			}
			while (first != end)
			{
				*first = *(first + distance);
				++first;
			}
			return (last);
		}

		void swap (vector<T, Allocator>& x)
		{
			T	*data_aux = _data;
			_data = x._data;
			x._data = data_aux;
		}

		void clear()
		{
			for (size_type i = 0; i < _size; ++i)
				_allocator.destroy(&_data[i]);
			_size = 0;
		}

		allocator_type get_allocator() const
		{
			return (_allocator);
		}

		// template <class T, class Allocator>
			bool operator== (const vector<T,Allocator>& rhs)
			{
				if (_size != rhs._size)
					return (false);
				for (size_type i = 0; i < _size; ++i)
				{
					if ((*this)[i] != rhs[i])
						return (false);
				}
				return (true);
			}
		// template <class T, class Alloc>
			bool operator!= (const vector<T,Allocator>& rhs)
			{
				return (!(*this == rhs));
			}
		// template <class T, class Alloc>
			bool operator< (const vector<T, Allocator>& rhs) //FIXME: a<b y b<a
			{
				for (size_type i = 0; i < _size && i < rhs._size; ++i)
				{
					if ((*this)[i] >= rhs[i])
						return (false);
				}
				return (true);
			}
		// template <class T, class Alloc>
			bool operator<= (const vector<T,Allocator>& rhs)
			{
				return (!(rhs < *this));
			}
		// template <class T, class Alloc>
			bool operator> (const vector<T,Allocator>& rhs)
			{
				return (rhs < *this);
			}
		// template <class T, class Alloc>
			bool operator>= (const vector<T,Allocator>& rhs)
			{
				return (!(*this < rhs));
			}

		// template <class T, class Alloc>
			void swap (vector<T,Allocator>& x, vector<T,Allocator>& y)
			{
				x.swap(y);
			}
};
}
#endif