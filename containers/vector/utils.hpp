#ifndef UTILS_HPP
# define UTILS_HPP

#include <cstdlib>

namespace ft {

	template < bool Cond, class T = void >
		struct enable_if {};
	template < class T >
		struct enable_if<true, T>
		{
			typedef T type;
		};

	template <class T, T val>
		struct integral_constant {
			static	const T value = val;
			typedef	T value_type;
			typedef	integral_constant<T, val> type;
			operator value_type() { return val; }
	};

	//Most longwinded way of saying const bool IN HISTORY
	//Should be banned by law
	struct true_type : public integral_constant<bool,true>
	{
		typedef true_type	type;
	};

	struct false_type : public integral_constant<bool,false>
	{
		typedef false_type	type;
	};
	// typedef integral_constant<bool,true> true_type;
	// typedef integral_constant<bool,false> false_type;


	template<typename T>
		struct is_integral : public false_type {};
	template <>
		struct is_integral<bool> : public true_type {};
	template <>
		struct is_integral<char> : public true_type {};
	template <>
		struct is_integral<int> : public true_type {};
	template <>
		struct is_integral<long int> : public true_type {};
	//and so on...

	template<typename T> //FIXME: creo que no lo utilizo
	struct	has_iterator_category {
		typedef char yes[1];
		typedef char no[2];

		template<typename C>
		static yes & test(typename C::iterator_category *);
		
		template<typename C>
		static no & test(...);

		static const bool value = sizeof(test<T>(NULL)) == sizeof(yes);
	};

	template < class From, class To >
		struct is_convertible_simple
		{
			typedef char yes[1];
			typedef char no[2];

			static yes & test(To);
			static no & test(...);
			static From returnFrom();

			static const bool value = (sizeof(test(returnFrom())) == sizeof(yes));
		};

	template < class From, class To >
		struct is_convertible
		: public integral_constant<bool, is_convertible_simple<From, To>::value> 
		{ };

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
	template<typename _Tp>
		struct iterator_traits<_Tp*>
		{
			typedef std::random_access_iterator_tag	iterator_category;
			typedef _Tp								value_type;
			typedef std::ptrdiff_t					difference_type;
			typedef _Tp*							pointer;
			typedef _Tp&							reference;
		};
	// CONST SPECIALIZATION
	template<typename _Tp>
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
	template <class InputIterator1, class InputIterator2>
		bool	equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
		{
			while (first1 != last1)
			{
				if (!(*first1 == *first2))
					return (false);
				++first1; ++first2;
			}
		}
	template< class InputIterator1, class InputIterator2 >
		bool	lexicographical_compare( InputIterator1 first1, InputIterator1 last1,
									InputIterator2 first2, InputIterator2 last2 )
		{
			while (first1 != last1)
			{
				if (first2 == last2 || *first2 < *first1)
					return (false);
				else if (*first1 < *first2)
					return (true);
				++first1; ++first2;
			}
			return (first2 != last2);
		}


	template <class T1, class T2>
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		first_type	first;
		second_type	second;

		// default
		pair(): first(first_type()), second(second_type()) {}

		// copy
		template <class U, class V>
			pair (const pair<U,V>& pr):
				first(first_type(pr.first)), second(second_type(pr.second)) {}
	
		// initialization
		pair (const first_type& a, const second_type& b): first(first_type(a)), second(second_type(b)) {}

	};
	
	template <class T1, class T2>
		bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return lhs.first == rhs.first && lhs.second == rhs.second; }

	template <class T1, class T2>
		bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return !(lhs == rhs); }
	
	template <class T1, class T2>
		bool operator< (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second); }

	template <class T1, class T2>
		bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return !(rhs < lhs); }

	template <class T1, class T2>
		bool operator> (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return rhs < lhs; }

	template <class T1, class T2>
		bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return !(lhs < rhs); }

	template <class T1,class T2>
		ft::pair<T1,T2> make_pair (T1 x, T2 y)
		{
			return (ft::pair<T1,T2>(x,y));
		}
}

#endif


// #if __cplusplus >= 201103L
//   template<typename _InIter>
//     using _RequireInputIter = typename
//       enable_if<is_convertible<typename iterator_traits<_InIter>::iterator_category, input_iterator_tag>::value>::type;
// #endif