#include "vector.hpp"
#include <iostream>
#include <stdio.h>
// #include <vector>
using namespace ft;
template <typename T>
	void	imprimir_variables(vector<T> contenedor)
	{
		std::cout << "---------------------------------------\n";
		typename vector<T>::iterator it = contenedor.begin();
		typename vector<T>::iterator end = contenedor.end();
		while (it != end)
		{
			std::cout << *it << '\n';
			++it;
		}
		std::cout << "Size: " << contenedor.size() << "\nCapacity: " << contenedor.capacity() << '\n';
		std::cout << "---------------------------------------\n";
	}

template <typename T>
	void	imprimir_variables_reves(vector<T> contenedor)
	{
		std::cout << "---------------------------------------\n";
		typename vector<T>::reverse_iterator rend = contenedor.rend();
		typename vector<T>::reverse_iterator rbegin = contenedor.rbegin();
		while (rbegin != rend)
		{
			std::cout << *rbegin << '\n';
			++rbegin;
		}
		std::cout << "Size: " << contenedor.size() << "\nCapacity: " << contenedor.capacity() << '\n';
		std::cout << "---------------------------------------\n";
	}

int main()
{
	// vector<int> contenedor(3);

	// imprimir_variables(contenedor);
	// contenedor.push_back(4);
	// imprimir_variables(contenedor);

	// vector<int>::iterator it = contenedor.begin();
	// it++;
	// contenedor.insert(it, 27);
	// imprimir_variables(contenedor);
	// vector<int>::iterator end = contenedor.end();
	// end--;
	// it = contenedor.begin();
	// contenedor.insert (it, 2, 69);
	// imprimir_variables(contenedor);
	// // contenedor.insert(contenedor.end() - 1, 3, 96);

	vector<int> test1(2, 69);
	vector<int> test2(5, 5);

	test2[4] = 7;
	test2.insert(test2.begin() + 2, test1.begin(), test1.end());
	// test2[0] = 3;
	imprimir_variables(test2);
	// imprimir_variables_reves(test2);
	
	// vector<int>test3(2, 200);
	// test2.insert(test2.begin() + 2, test3.begin(), test3.end());
	test2.insert(test2.begin() + 2, 2, 200);
	imprimir_variables(test2);


	vector<int>::iterator it = test2.insert(test2.begin(), 900);
	for (vector<int>::iterator end = test2.end(); it != end; ++it)
		std::cout << *it << '\n';
	test2.erase(test2.end() - 1);
	imprimir_variables(test2);
	test2.erase(test2.begin() + 1, test2.begin() + 3);
	imprimir_variables(test2);
}
