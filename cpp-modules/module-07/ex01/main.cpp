#include "iter.hpp"
#include <iostream>
#include <string>

std::ostream &operator<<(std::ostream &os, Example const &a) { os << a.number; return (os); }

void	decrement(int &n)
{
	n--;
}

void	ft_toupper(char &n)
{
	n = toupper(n);
}

int main( void )
{
	int array[4] = {1, 2, 3, 4};
	iter(array, 4, decrement);
	// prints array values
	for (int i = 0; i < 4; i++)
		std::cout << array[i];
	std::cout << '\n';
	// increments array values
	iter(array, 4, template_increment<int>);
	// prints them again
	for (int i = 0; i < 4; i++)
		std::cout << array[i];
	std::cout << '\n';
	
	std::string string1 = "hello there !";
	iter((char*)string1.c_str(), string1.length(), ft_toupper);
	std::cout << '\n' << string1 << "\n\n";

	Example array_example[5];
	iter(array_example, 5, template_print<Example>);
	return (0);
}
