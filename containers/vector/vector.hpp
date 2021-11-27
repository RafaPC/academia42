// #ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include <iterator>
#include <limits>
#include <cstdlib>
#include <exception>
#include <memory>
#include <iostream>
#include "vector_iterator.hpp"
#include "utils.hpp"

//TODO: checkear cuando dejo como elementos desepués de acabar el size y antes de acabarse de verdad el vector
// creo que no hay problema porque suelen ser elementos que tienen su copia en otro lado antes del size
// pero puede que dejar elementos despues del size esté mal y tenga que destruirlos siempre
namespace ft {

template < class T, class Allocator = std::allocator<T> >
class vector
{
	public:
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
		typedef size_t											size_type; //FIXME:
		typedef std::ptrdiff_t									difference_type;

	private:
		T			*_data;
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
				std::cout << "Constructor original de numeritos\n";
				this->_data = this->_allocator.allocate(n);
				while (n--)
					this->_allocator.construct(&this->_data[n], val);
			}
		
		
		template <typename InputIterator> // no es un numerito
			void	otra_funcion(InputIterator first, InputIterator last, false_type)
			{
				// Esto sirve para diferenciar la funcionalidad entre forward_iterator_tag e input_iterator_tag
				std::cout << "falsa" << std::endl;
				// typedef typename std::iterator_traits<InputIterator>::iterator_category _IterCategory;
				// std::cout << "InputIterator is integral:" << _Integral() << '\n';
				this->_capacity = std::distance(first, last);
				this->_size = this->_capacity;
				this->_data = this->_allocator.allocate(this->_capacity);
				iterator	it = this->begin();
				while (first != last)
				{
					this->_allocator.construct(it, *first); //FIXME: ver si funciona esto, si no con un size_type i
					it++;
					first++;
				}
			}
		template <typename Integer> // es un numerito
			void	otra_funcion(Integer _n, Integer val, true_type)
			{
				size_type n = static_cast<size_type>(_n);
				this->_size = n;
				this->_data = this->_allocator.allocate(n);
				this->_capacity = n;
				while (n--)
					this->_allocator.construct(&this->_data[n], static_cast<value_type>(val));
				std::cout << "true" << std::endl;
			}
		
		template <typename InputIterator>
		vector (InputIterator first, InputIterator last,
			const allocator_type& alloc = allocator_type(),
			typename enable_if<is_convertible<typename InputIterator::iterator_category, std::input_iterator_tag>::value, void>::type* = NULL)
			: _size(std::distance(first, last)), _capacity(_size), _allocator(alloc)
			{
				// std::cout << "Entra" << std::endl;
				// typedef typename ft::is_integral<InputIterator>::type _Integral;
				// otra_funcion(first, last, _Integral());
				// std::cout << "InputIterator is integral:" << _Integral() << '\n';

				// this->_capacity = std::distance(first, last);
				// this->_size = this->_capacity;
				this->_data = this->_allocator.allocate(this->_capacity);
				for (size_type i = 0; first != last; i++, first++)
					this->_allocator.construct(this->_data + i, *first);
			}
		vector (const vector& x)
		{
			this->_data = NULL;
			*this = x;
		}

		//	DESTRUCTOR
		~vector()
		{
			for (size_type i = 0; i < this->_size; i++)
				this->_allocator.destroy(&this->_data[i]);
			this->_allocator.deallocate(this->_data, this->_capacity);
		}

		//TODO: checkear, si el nuevo tamaño es menor que el anterior, utilizar el mismo puntero _data
		//TODO: checkear si x._data == NULL
		vector& operator= (const vector& x)
		{
			if (this->_data == NULL)
				this->_data = this->_allocator.allocate(x._capacity, x._data);
			else
			{
				for (size_type i = 0; i < this->_size; i++)
					this->_allocator.destroy(&this->_data[i]);
				if (this->_capacity < x._size)
				{
					pointer	aux_data = this->_allocator.allocate(x._size, this->_data);
					this->_allocator.deallocate(this->_data, this->_capacity);
					this->_data = aux_data;
				}
			}
			this->_capacity = x._size;
			this->_size = x._size;
			for (size_type i = 0; i < this->_size; i++)
				this->_allocator.construct(&this->_data[i], x._data[i]);
			return (*this);
		}

		// ITERATORS
		iterator				begin()
		{
			return (iterator(this->_data));
		}
		const_iterator			begin() const
		{
			return (const_iterator(this->_data));
		}
		iterator				end()
		{
			return (iterator(&this->_data[this->_size]));
		}
		const_iterator			end() const
		{
			return (iterator(&this->_data[this->_size]));
		}
		reverse_iterator		rbegin()
		{
			return (reverse_iterator(&this->_data[this->_size]));
		}
		const_reverse_iterator	rbegin() const
		{
			return (const_reverse_iterator(&this->_data[this->_size]));
		}
		reverse_iterator		rend()
		{
			return (reverse_iterator(this->_data));
		}
		const_reverse_iterator	rend() const
		{
			return (const_reverse_iterator(this->_data));
		}

		// CAPACITY
		size_type	size() const
		{
			return (this->_size);
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
			while (new_size > this->_size)
				this->pop_back();
			while (new_size > this->_size)
				this->push_back(val);
			if (new_size > this->capacity)
				this->reserve(new_size);
		}
		bool		empty() const
		{
			return (this->_size == 0);
		}
		void		reserve(size_type new_capacity)
		{
			if (new_capacity > this->max_size())
				throw std::length_error("size requested is greater than maximum size");
			else if (new_capacity > this->_capacity)
			{
				pointer new_data = this->_allocator.allocate(new_capacity, this->_data);
				for (size_type i = 0; i < this->_size; i++)
				{
					this->_allocator.construct(&new_data[i], this->_data[i]);
					this->_allocator.destroy(&this->_data[i]);
				}
				this->_allocator.deallocate(this->_data, this->_capacity);
				this->_data = new_data;
				this->_capacity = new_capacity;
			}
		}

		// ELEMENT ACCESS
		reference 		operator[] (size_type n)
		{
			return (this->_data[n]);
		}
		const_reference operator[] (size_type n) const
		{
			return (this->_data[n]);
		}
		reference 		at (size_type n)
		{
			if (n >= this->size) //FIXME: maybe hacer que llame a check_range
				throw (std::out_of_range("number out of range")); //FIXME: poner mensagito guay
			return (this->_data[n]);
		}
		const_reference at (size_type n) const
		{
			if (n >= this->size)
				throw (std::out_of_range("number out of range")); //FIXME: mensajito guay
			return (this->_data[n]);
		}
		reference 		front()
		{
			return (this->_data[0]);
		}
		const_reference front() const
		{
			return (this->_data[0]);
		}
		reference 		back()
		{
			return (this->_data[this->_size - 1]);
		}
		const_reference back() const
		{
			return (this->_data[this->_size - 1]);
		}

		// MODIFIERS
		template <class InputIterator>
			void	assign(InputIterator first, InputIterator last)
			{
				const size_type	new_size = std::distance(first, last);
				if (new_size > this->_capacity)
					this->reserve(new_size);
				else
					this->clear();
				for (size_type i = 0; first != last; ++i, ++first)
					this->_allocator.construct(&this->_data[i], *first);
			}
		void assign (size_type n, const value_type& val)
		{
			if (n > this->capacity)
				this->reserve(n);
			this->_size = n;
			while (n--)
				this->_allocator.construct(&this->_data[n], val);
		}
		//The content of val is copied (or moved) to the new element.
		void push_back (const value_type& val)
		{
			if (this->_size == this->_capacity)
				this->reserve(this->_capacity + 1);
			this->_allocator.construct(&this->_data[this->_size], val);
			this->_size++;
		}
		void pop_back()
		{
			this->_allocator.destroy(&this->_data[this->_size - 1]);
			this->_size--;
		}
		iterator insert (iterator position, const value_type& val)
		{
			const size_type distance = std::distance(this->begin(), position);
			if (this->_size == this->_capacity)
				this->reserve(this->_capacity + 1);

			iterator end = this->end();
			iterator it = this->begin() + distance + 1;
			while (it != end)
			{
				*it = *(it - 1);
				it++;
			}
			this->_allocator.construct(&this->_data[distance], val);
			this->_size++;
			return (position); //FIXME: pensar si está bien
		}

		void insert (iterator position, size_type n, const value_type& val)
		{
			const size_type distance = std::distance(this->begin(), position);
			const size_type added_capacity = this->_size + n - this->_capacity;
			if (added_capacity > 0)
				this->reserve(this->_capacity + added_capacity);

			iterator end = this->end();
			iterator it = this->begin() + distance + n;
			while (it != end)		//FIXME: esto no parece hacer lo que debe
			{
				*it = *(it - n);
				it++;
			}
			for (size_type i = 0; i < n; i++)
				this->_allocator.construct(&this->_data[distance + i], val);
		}

		// Additionally, if InputIterator in the range insert (3) is not at least of a forward
		// iterator category (i.e., just an input iterator) the new capacity cannot be determined 
		// beforehand and the insertion incurs in additional logarithmic complexity in size (reallocations).
		
		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last,
		typename enable_if<is_convertible<typename InputIterator::iterator_category, std::input_iterator_tag>::value, void>::type* = NULL)
		{
			const size_type range_distance = std::distance(first, last);
			const size_type	new_size = _size + range_distance;

			if (new_size > this->_capacity)
			{
				const size_type position_i = std::distance(begin(), position);
				this->reserve(this->_size + range_distance);
				position = &_data[position_i];
			}
			this->_size = new_size;
			iterator end = this->end();
			iterator it = position + range_distance; //TODO:
			// mover los elementos antiguos range_distance posiciones a la derecha
			while (it != end)
			{
				*it = *(it - range_distance);
				++it;
			}
			it = position;
			size_type i = std::distance(begin(), position);
			while (first != last)
			{
				this->_allocator.construct(&_data[i], *first);
				++i;
				++first;
			}
		};

		iterator erase (iterator position)
		{
			this->_allocator.destroy(position);
			this->_size--;
			if (position != this->end())
			{
				iterator	it = position + 1;
				iterator	end = this->end();
				while (it != end)
				{
					*(it - 1) = *it;
					it++;
				}
			}
			return (position);
		}
		iterator erase (iterator first, iterator last)
		{
			iterator		it = first;
			const size_type	distance = std::distance(first, last);
			this->_size -= distance;
			iterator		end = this->end();

			while (it != last)
			{
				this->_allocator.destroy(it);
				it++;
			}
			while (first != (end - distance))
			{
				*first = *(first + distance);
				first++;
			}
			return (last);
		}

		void swap (vector<T, Allocator>& x)
		{
			T	*data_aux = this->_data;
			this->_data = x._data;
			x._data = data_aux;
		}

		void clear()
		{
			for (size_type i = 0; i < this->_size; i++)
				this->_allocator.destroy(&this->_data[i]);
			this->_size = 0;
		}

		allocator_type get_allocator() const
		{
			return (this->_allocator);
		}

		// template <class T, class Allocator>
			bool operator== (const vector<T,Allocator>& rhs)
			{
				if (this->_size != rhs._size)
					return (false);
				for (size_type i = 0; i < this->_size; i++)
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
			bool operator< (const vector<T,Allocator>& rhs) //FIXME: a<b y b<a
			{
				for (size_type i = 0; i < this->_size && i < rhs._size; i++)
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
// #endif