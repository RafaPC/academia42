#include "vector.hpp"
#include <iostream>
#include <stdio.h>
// #include <vector>
using namespace ft;
template <typename T>
	void	imprimir_variables(vector<T> contenedor)
	{
		for (size_t i = 0; i < contenedor.size(); i++)
			std::cout << contenedor[i] << '\n';
		std::cout << "Size: " << contenedor.size() << "\nCapacity: " << contenedor.capacity() << '\n';
	}

template <typename T>
	void	imprimir_variables_reves(vector<T> contenedor)
	{
		typename vector<T>::reverse_iterator rend = contenedor.rend();
		typename vector<T>::reverse_iterator rbegin = contenedor.rbegin();
		while (rbegin != rend)
		{
			std::cout << *rbegin << '\n';
			++rbegin;
		}
		std::cout << "Size: " << contenedor.size() << "\nCapacity: " << contenedor.capacity() << '\n';
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

	vector<int> test1(3, 69);
	vector<int> test2(5, 5);

	test2.insert(test2.begin() + 2, test1.begin(), test1.end());
	test2[0] = 3;
	imprimir_variables(test2);
	imprimir_variables_reves(test2);

	// std::cout << sizeof(ft::iterator_traits<ft::vector<int>::iterator>::iterator_category);

}
