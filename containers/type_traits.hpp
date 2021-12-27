#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

namespace ft
{
	template < bool Cond, class T = void >
		struct enable_if {};
	template < class T >
		struct enable_if<true, T>
		{
			typedef T type;
		};

	template <class T, T val>
		struct integral_constant
		{
			static	const T value = val;
			typedef	T value_type;
			typedef	integral_constant<T, val> type;
			operator value_type() { return val; }
		};

	struct true_type : public integral_constant<bool,true>
	{
		typedef true_type	type;
	};

	struct false_type : public integral_constant<bool,false>
	{
		typedef false_type	type;
	};

	template<typename T>
		struct is_integral : public false_type {};
	template <>
		struct is_integral<bool> : public true_type {};
	template <>
		struct is_integral<char> : public true_type {};
	template <>
		struct is_integral<signed char> : public true_type {};
	template <>
		struct is_integral<short int> : public true_type {};
	template <>
		struct is_integral<int> : public true_type {};
	template <>
		struct is_integral<long int> : public true_type {};
	template <>
		struct is_integral<long long int> : public true_type {};
	template <>
		struct is_integral<unsigned char> : public true_type {};
	template <>
		struct is_integral<unsigned short int> : public true_type {};
	template <>
		struct is_integral<unsigned int> : public true_type {};
	template <>
		struct is_integral<unsigned long int> : public true_type {};
	template <>
		struct is_integral<unsigned long long int> : public true_type {};

}

#endif