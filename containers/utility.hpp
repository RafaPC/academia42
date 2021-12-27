#ifndef UTILITY_HPP
# define UTILITY_HPP

namespace ft
{

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