#include <vector>
#include <iostream>
#include "easyfind.hpp"

int main( void )
{
	std::vector<int> vector;

	vector.push_back(1);
	vector.push_back(242);
	vector.push_back(3);
	vector.push_back(4);
	vector.push_back(37);
	vector.push_back(-6);
	
	try
	{
		std::vector<int>::const_iterator it = easyfind(vector, 242);
		if (it != vector.end())
			std::cout << "Number found: " << *it << '\n';
	}
	catch (const std::exception &e)
	{
		std::cout << "Exception\n";
	}

	try
	{
		std::vector<int>::const_iterator it = easyfind(vector, -24);
		if (it != vector.end())
			std::cout << "Number found: " << *it << '\n';
	}
	catch (const std::exception &e)
	{
		std::cout << "Exception handled, number -24 not found in the vector\n";
	}
	return 0;
}
