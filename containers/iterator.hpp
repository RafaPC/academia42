#ifndef ITERATOR_HPP
# define ITERATOR_HPP

namespace ft
{
	template <class Iterator>
		struct iterator_traits
		{
			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;
			typedef typename Iterator::iterator_category	iterator_category;
		};
	// POITNER SPECIALIZATION
	template <typename _Tp>
		struct iterator_traits<_Tp*>
		{
			typedef std::random_access_iterator_tag	iterator_category;
			typedef _Tp								value_type;
			typedef std::ptrdiff_t					difference_type;
			typedef _Tp*							pointer;
			typedef _Tp&							reference;
		};
	// CONST SPECIALIZATION
	template <typename _Tp>
		struct iterator_traits<const _Tp*>
		{
			typedef std::random_access_iterator_tag	iterator_category;
			typedef _Tp								value_type;
			typedef std::ptrdiff_t					difference_type;
			typedef const _Tp*							pointer;
			typedef const _Tp&							reference;
		};

	template <class Iterator>
		class reverse_iterator
		{
			public:
				typedef Iterator iterator_type;
				typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
				typedef typename	iterator_traits<Iterator>::value_type		value_type;
				typedef typename	iterator_traits<Iterator>::difference_type	difference_type;
				typedef typename	iterator_traits<Iterator>::pointer			pointer;
				typedef typename	iterator_traits<Iterator>::reference		reference;
			protected:
				iterator_type	current;
			public:
				//default
				reverse_iterator(void) : current(Iterator()) {}

				//initialization
				explicit	reverse_iterator (iterator_type it)
				:current(it) {}

				//copy
				template <class Iter>
					reverse_iterator (const reverse_iterator<Iter>& other)
					: current(other.current) {}

				iterator_type base() const { return (current); }
				reference operator*() const
				{
					iterator_type temp = current;
					return *--temp;
				}
				pointer operator->() const
				{
					return &(operator* ());
				}
				//FIXME: no sé si está bien
				reference operator[]( difference_type n ) const
				{
					return (current[-n - 1]);
				}
				reverse_iterator& operator++()
				{
					--current;
					return (*this);
				}
				reverse_iterator operator++( int )
				{
					reverse_iterator temp(current);
					--current;
					return (temp);
				}
				reverse_iterator& operator--()
				{
					++current;
					return (*this);
				}
				reverse_iterator operator--( int )
				{
					reverse_iterator temp(current);
					++current;
					return (temp);
				}
				reverse_iterator operator+ (difference_type n) const
				{
					return (reverse_iterator(current - n));
				}
				reverse_iterator& operator+=( difference_type n )
				{
					*this = *this + n;
					return (*this);
				}
				reverse_iterator operator- (difference_type n) const
				{
					return (reverse_iterator(current + n));
				}
				reverse_iterator& operator-=( difference_type n )
				{
					*this = *this - n;
					return (*this);
				}
				bool operator== (const reverse_iterator &x) const
				{
					return (current == x.current);
				}
				bool operator!= (const reverse_iterator &x) const
				{
					return (current != x.current);
				}
				bool operator> (const reverse_iterator &x) const
				{
					return (current < x.current);
				}
				bool operator>= (const reverse_iterator &x) const
				{
					return (current <= x.current);
				}
				bool operator< (const reverse_iterator &x) const
				{
					return (current > x.current);
				}
				bool operator<= (const reverse_iterator &x) const
				{
					return (current >= x.current);
				}
		};


}


#endif