#ifndef UTILS_HPP
# define UTILS_HPP

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

	template<typename T>
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
		class iterator_traits
		{
			public:
				typedef typename Iterator::difference_type		difference_type;
				typedef typename Iterator::value_type			value_type;
				typedef typename Iterator::pointer				pointer;
				typedef typename Iterator::reference			reference;
				typedef typename Iterator::iterator_category	iterator_category;
		};

	template <class Iterator>
		class reverse_iterator
		{
			//TODO: a ver, igual que para el iterador normal, el + y el - si es random_access se hace
			// con la suma y la resta directamente, se puede hacer que siempre sea a base de unos
			// cuantos ++'s y --'s pero lo suyo es hacer la sobrecarga con el checkeo de tipos en compilacion
			// comprobar si el tipo es convertible a std::random_access.... y si lo es, hacerlo con
			// suma y resta directamente
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
				reverse_iterator();

				//initialization
				explicit	reverse_iterator (iterator_type it)
				:current(it) {}

				//copy
				// The underlying iterator is initialized with that of other.
				// This overload participates inoverload resolution only if U is not
				// the same type as Iter and std::convertible_to<const U&, Iter> is modeled (since C++20)
				//TODO: añadir cositas de tipos al compilar
				template <class Iter>
					reverse_iterator (const reverse_iterator<Iter>& rev_it)
					{
						
					}
				iterator_type base() const { return (current + 1); }
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
				// TODO: version si es random...
				// reverse_iterator operator+ (difference_type n) const
				// {
				// 	return (reverse_iterator(current - n));
				// }
				reverse_iterator operator+ (difference_type n) const
				{
					reverse_iterator temp(current);
					while (n--)
						++temp;
					return (temp);
				}
				reverse_iterator& operator+=( difference_type n )
				{
					*this = *this + n;
					return (*this);
				}
				// TODO: version si es random...
				// reverse_iterator operator- (difference_type n) const
				// {
				// 	return (reverse_iterator(current + n));
				// }
				reverse_iterator operator- (difference_type n) const
				{
					reverse_iterator temp(current);
					while (n--)
						--temp;
					return (temp);
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


// #if __cplusplus >= 201103L
//   template<typename _InIter>
//     using _RequireInputIter = typename
//       enable_if<is_convertible<typename iterator_traits<_InIter>::iterator_category, input_iterator_tag>::value>::type;
// #endif