#ifndef ITER_HPP
# define ITER_HPP

#include <iostream>

template <typename T>
void	iter(T array[], int length, void (*f)(T &x) )
{
	for (int i = 0; i < length; i++)
		f(array[i]);
}

/*
**		EXAMPLES DECLARATIONS
*/
template <typename T>
void	template_print(T &x)
{
	std::cout << x << '\n';
}

template <typename T>
void	template_increment(T &x)
{
	x++;
}

class Example
{
	public:
		int number;
		Example(void): number(42) {};
};
std::ostream &operator<<(std::ostream &os, Example const &a);

#endif