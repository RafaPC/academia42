#ifndef ITERATOR_HPP
# define ITERATOR_HPP

namespace ft
{
	template <typename Type>
		struct iterator_traits
		{
			typedef typename Type::difference_type		difference_type;
			typedef typename Type::value_type			value_type;
			typedef typename Type::pointer				pointer;
			typedef typename Type::reference			reference;
			typedef typename Type::iterator_category	iterator_category;
		};

	// POITNER SPECIALIZATION
	template <typename Type>
		struct iterator_traits<Type*>
		{
			typedef std::random_access_iterator_tag		iterator_category;
			typedef Type								value_type;
			typedef std::ptrdiff_t						difference_type;
			typedef Type*								pointer;
			typedef Type&								reference;
		};

	// CONST SPECIALIZATION
	template <typename Type>
		struct iterator_traits<const Type*>
		{
			typedef std::random_access_iterator_tag		iterator_category;
			typedef Type								value_type;
			typedef std::ptrdiff_t						difference_type;
			typedef const Type*							pointer;
			typedef const Type&							reference;
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
				explicit	reverse_iterator (iterator_type it): current(it){ }

				//copy
				template <class Iter>
					reverse_iterator (const reverse_iterator<Iter>& other)
					: current(other.base()) {}

				template< class U >
					reverse_iterator& operator=( const reverse_iterator<U>& other )
					{
						current = other.base();
						return (*this);
					}

				iterator_type base() const { return (current); }

				reference operator*() const
				{
					iterator_type temp(current);
					return *--temp;
				}

				pointer operator->() const
				{
					return &(operator* ());
				}

				reference operator[]( difference_type n ) const
				{
					return (base()[-n - 1]);
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

				reverse_iterator& operator-=(difference_type n)
				{
					*this = *this - n;
					return (*this);
				}
		};

	template <class Iterator, class Iterator2>
		typename reverse_iterator<Iterator>::difference_type	operator-(
			const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator2> &rhs)
		{
			return rhs.base().base() - lhs.base().base();
		};

	template <class Iterator, class Iterator2>
		bool operator== (const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator2> &rhs)
		{
			return (lhs.base() == rhs.base());
		}

	template <class Iterator, class Iterator2>
		bool operator!= (const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator2> &rhs)
		{
			return (lhs.base() != rhs.base());
		}

	template <class Iterator, class Iterator2>
		bool operator< (const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator2> &rhs)
		{
			return (lhs.base() > rhs.base());
		}

	template <class Iterator, class Iterator2>
		bool operator<= (const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator2> &rhs)
		{
			return (lhs.base() >= rhs.base());
		}

	template <class Iterator, class Iterator2>
		bool operator> (const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator2> &rhs)
		{
			return (lhs.base() < rhs.base());
		}

	template <class Iterator, class Iterator2>
		bool operator>= (const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator2> &rhs)
		{
			return (lhs.base() <= rhs.base());
		}

	template <class Iterator>
		typename reverse_iterator<Iterator>::difference_type operator- (
			const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs)
		{
			return (rhs.base() - lhs.base());
		}

	template <class Iterator>
		reverse_iterator<Iterator> operator+ (
			typename reverse_iterator<Iterator>::difference_type n,
			const reverse_iterator<Iterator>& rev_it)
		{
			return (rev_it + n);
		}

}

#endif