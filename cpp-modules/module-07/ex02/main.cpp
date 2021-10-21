#include <iostream>
#include <string>
#include "Array.hpp"

int main( void )
{
	std::cout << "Empty array tests:\n";
	Array<int> empty = Array<int>(0);
	try
	{
		empty[0];
	}
	catch (const std::exception& e)
	{
		std::cout << "Exception: " << e.what() << '\n';
	}

	std::cout << "\nInt array tests:\n";
	Array<int> array = Array<int>(5);
	for (int i = 0; i < array.size(); i++)
	{
		array[i] = i;
		std::cout << array[i] << '|';
	}
	std::cout << '\n';
	for (int i = 0; i < array.size(); i++)
	{
		array[i]++;
		std::cout << array[i] << '|';
	}
	try
	{
		array[6];
	}
	catch (const std::exception& e)
	{
		std::cout << "\nException: " << e.what() << '\n';
	}

	std::cout << "\nString tests:\n";
	Array<std::string> array_string = Array<std::string>(3);
	array_string[0] = "hello";
	array_string[1] = "world!";
	array_string[2] = ":D";
	for (int i = 0; i < array_string.size(); i++)
		std::cout << array_string[i] << ' ';
	std::cout << '\n';

	std::cout << "\nCopy array tests:\n";
	Array<std::string> copied_array = array_string;
	copied_array[1] = "mom!";
	for (int i = 0; i < copied_array.size(); i++)
		std::cout << copied_array[i] << ' ';
	std::cout << '\n';
	for (int i = 0; i < array_string.size(); i++)
		std::cout << array_string[i] << ' ';
	std::cout << '\n';
	
	// std::cout << "\nConst values tests:\n";
	// const Array<int> test = Array<int>(1);
	// std::cout << test[0] << '\n';
	// test[0] = 3;
	// std::cout << test[0] << '\n';
	return 0;
}
