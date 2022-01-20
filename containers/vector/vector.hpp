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
#include "../iterator.hpp"
#include "../algorithm.hpp"
#include "../type_traits.hpp"

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
		typedef ft::VectorIterator<value_type>					iterator;
		typedef ft::VectorIterator<const value_type>			const_iterator;
		typedef ft::reverse_iterator<iterator>					reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
		typedef size_t											size_type;
		typedef std::ptrdiff_t									difference_type;

	private:
		value_type	*_data;
		size_type	_size;
		size_type	_capacity;
		Allocator	_allocator;

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

		template <typename Iterator>
		vector (Iterator first, Iterator last,
			const allocator_type& alloc = allocator_type(),
			typename ft::enable_if<!ft::is_integral<Iterator>::value, Iterator>::type* = NULL): _allocator(alloc)
			{
				typedef typename ft::iterator_traits<Iterator>::iterator_category IteratorCategory;
				_constructor_range(first, last, IteratorCategory());
			}

		vector (const vector& x): _data(NULL)
		{
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
		iterator				begin() { return (iterator(_data)); }
		
		const_iterator			begin() const { return (const_iterator(_data)); }
		
		iterator				end() { return (iterator(_data + _size)); }
		
		const_iterator			end() const { return (const_iterator(_data + _size)); }

		reverse_iterator		rbegin() { return (reverse_iterator(_data + _size)); }
		
		const_reverse_iterator	rbegin() const { return (const_reverse_iterator(_data + _size)); }
		
		reverse_iterator		rend() { return (reverse_iterator(_data)); }
		
		const_reverse_iterator	rend() const { return (const_reverse_iterator(_data)); }

		// CAPACITY
		size_type	size() const { return (_size); }
		
		size_type	max_size() const { return (_allocator.max_size()); }
		
		size_type	capacity() const { return (_capacity); }
		
		/*
		**	If the new size is smaller than the current one, calls pop_back() as many times the difference
		**	If the new size is greater than the current one, reserves the needed capacity
		**	and pushes as many values as needed
		*/
		void		resize(size_type new_size, value_type val = value_type())
		{
			while (new_size < _size)
				pop_back();
			if (new_size > _capacity)
				reserve(new_size);
			while (new_size > _size)
				push_back(val);
		}
		
		bool		empty() const { return (_size == 0); }
		
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
					_allocator.construct(&new_data[i], _data[i]);

				_allocator.deallocate(_data, _capacity);
				_data = new_data;
				_capacity = new_capacity;
			}
		}

		// ELEMENT ACCESS
		
		reference 		operator[] (size_type n) { return (_data[n]); }

		const_reference operator[] (size_type n) const { return (_data + n); }

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

		reference 		front() { return (_data[0]); }

		const_reference front() const { return (_data[0]); }

		reference 		back() { return (_data[_size - 1]); }

		const_reference back() const { return (_data[_size - 1]); }

		template <class Iterator>
			void	assign(Iterator first, Iterator last,
			typename ft::enable_if<!ft::is_integral<Iterator>::value, Iterator>::type* = NULL)
			{
				typedef typename ft::iterator_traits<Iterator>::iterator_category IteratorCategory;
				_assign_range(first, last, IteratorCategory());
			}

		void assign (size_type n, const value_type& val)
		{
			clear();
			reserve(n);
			_size = n;
			for (size_type i = 0; i < n; ++i)
				_allocator.construct(&_data[i], val);
		}

		void push_back (const value_type& val)
		{
			reserve(_size + 1);
			_allocator.construct(&_data[_size++], val);
		}

		void pop_back() { _allocator.destroy(&_data[--_size]); }

		iterator	insert (iterator position, const value_type& val)
		{
			const size_type position_index = position - begin();
			reserve(_size + 1);
			++_size;
			// it sets each position value by its previous one from end to the position
			// of the inserted element
			_right_shift_elements(position_index + 1, 1);

			_allocator.construct(&_data[position_index], val);
			return (&_data[position_index]);
		}

		void	insert (iterator position, size_type n, const value_type& val)
		{
			if (n == 0)
				return;
			const size_type start_index = position - begin();
			reserve(_size + n);
			_size += n;

			_right_shift_elements(start_index + n, n);
			for (size_type i = 0; i < n; ++i)
				_allocator.construct(&_data[start_index + i], val);
		}

		template <class Iterator>
			void	insert (iterator position, Iterator first, Iterator last,
			typename ft::enable_if<!ft::is_integral<Iterator>::value, Iterator>::type* = NULL)
			{
				typedef typename ft::iterator_traits<Iterator>::iterator_category IteratorCategory;
				_insert_range(position, first, last, IteratorCategory());
			};

		/*
		**	Destroys the element at position
		**	Then left shifts every element from position + 1 to the end
		**	Then pops_back the last element because it's duplicated
		*/
		iterator erase (iterator position)
		{
			_allocator.destroy(&*position);
			for (iterator it = position, end = this->end(); it + 1 != end; ++it)
				*it = *(it + 1);
			pop_back();
			return (position);
		}

		/*
		**	Destroys elements from first to last
		**	Shifts left erase_size positions each element from last to the end of the vector
		**	Then pops_back the remaining duplicated elements
		*/
		iterator erase (iterator first, iterator last)
		{
			const size_type	erase_size = last - first;

			for (iterator it = first; it != last; ++it)
				_allocator.destroy(&*it);

			for (iterator end = this->end(); first + erase_size != end; ++first)
				*first = *(first + erase_size);

			for (size_type i = 0; i < erase_size; ++i)
				pop_back();
			return (last - erase_size);
		}

		void swap (vector<T, Allocator>& other)
		{
			std::swap(_data, other._data);
			std::swap(_size, other._size);
			std::swap(_capacity, other._capacity);
			std::swap(_allocator, other._allocator);
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

	private:

		//If n is greater than the size, it throws an out of range exception with the appropiate message
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

		// Right shifts shift_length times every element from end to until_index
		void	_right_shift_elements(size_type until_index, size_type shift_length)
		{
			for (size_type i = _size - 1; i >= until_index; --i)
				_data[i] = _data[i - shift_length];
		}

		template <typename InputIterator>
			void _constructor_range (InputIterator first, InputIterator last, std::input_iterator_tag)
			{
				try
				{
					for (; first != last; ++first)
						push_back(*first);
				}
				catch (...)
				{
					clear();
					throw;
				}
			}

		template <typename Iterator>
			void _constructor_range (Iterator first, Iterator last, std::forward_iterator_tag)
			{
				_size = std::distance(first, last);
				_capacity = _size;
				_data = _allocator.allocate(_capacity);
				for (size_type i = 0; first != last; ++i, ++first)
					_allocator.construct(_data + i, *first);
			}

		// ASSIGN

		// called when InputIterator is an input iterator
		template <typename InputIterator>
			void	_assign_range(InputIterator first, InputIterator last, std::input_iterator_tag)
			{
				clear();
				for (; first != last; ++first)
					push_back(*first);
			}

		// called when InputIterator is at least a forward iterator
		template <typename Iterator>
			void	_assign_range(Iterator first, Iterator last, std::forward_iterator_tag)
			{
				const size_type	new_size = std::distance(first, last);
				clear();
				reserve(new_size);
				_size = new_size;
				for (size_type i = 0; first != last; ++i, ++first)
					_allocator.construct(&_data[i], *first);
			}

		// INSERT

		template <class InputIterator>
			void	_insert_range (iterator position, InputIterator first, InputIterator last, std::input_iterator_tag)
			{
				const size_type	position_index = std::distance(begin(), position);
				for (; first != last; ++first)
				{
					resize(_size + 1);
					_right_shift_elements(position_index, 1);
					_allocator.construct(&_data[position_index], *first);
				}
			};

		template <class Iterator>
			void	_insert_range (iterator position, Iterator first, Iterator last, std::forward_iterator_tag)
			{
				const size_type		new_elements_size = std::distance(first, last);
				if (new_elements_size == 0)
					return;
				size_type			insert_index = std::distance(begin(), position);

				reserve(_size + new_elements_size);
				_size += new_elements_size;
				// Elements from position are moved new_elements_size to the right
				// in reverse order so that no elements are removed
				_right_shift_elements(insert_index + new_elements_size, new_elements_size);
				// New elements are inserted
				for (; first != last; ++insert_index, ++first)
					_allocator.construct(&_data[insert_index], *first);
			};

};

template <class T, class Allocator>
	bool	operator== (const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs)
	{
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	};

template <class T, class Allocator>
	bool	operator!= (const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs)
	{
		return (!(lhs == rhs));
	};

template <class T, class Allocator>
	bool	operator< (const vector<T,Allocator>& lhs, const vector<T, Allocator>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	};

template <class T, class Allocator>
	bool	operator<= (const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs)
	{
		return (!(rhs < lhs));
	};

template <class T, class Allocator>
	bool	operator> (const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs)
	{
		return (rhs < lhs);
	};

template <class T, class Allocator>
	bool	operator>= (const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs)
	{
		return (!(lhs < rhs));
	};

template <class T, class Allocator>
	void	swap (vector<T,Allocator>& x, vector<T,Allocator>& y)
	{
		x.swap(y);
	};
}

#endif