#ifndef WHATEVER_HPP
# define WHATEVER_HPP

template <typename T>
T	max(T a, T b) { return (a > b ? a : b); }

template <typename T>
T	min(T a, T b) { return (a < b ? a : b); }

template <typename T>
void		swap(T &a, T &b)
{
	T aux = a;
	a = b;
	b = aux;
}

/*
**		EXAMPLE CLASS
*/
class	Example
{
	public:
		int	number;
		Example(int n): number(n) {}
		bool	operator >( Example & rhs )	const;
		bool	operator <( Example & rhs )	const;
};
std::ostream &operator<<(std::ostream &os, Example const &a);

#endif