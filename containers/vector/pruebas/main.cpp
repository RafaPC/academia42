#include "vector.hpp"
#include <iostream>
#include <stdio.h>
#include <vector>
using namespace ft;
template <typename T>
	void	imprimir_variables(vector<T> contenedor)
	{
		for (int i = 0; i < contenedor.size(); i++)
			std::cout << contenedor[i] << '\n';
		std::cout << "Size: " << contenedor.size() << "\nCapacity: " << contenedor.capacity() << '\n';
	}
int main(int argc, char const *argv[])
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

	ft::vector<int> vector(2, 10);
	// ft::vector<int> prueba(vector.begin(), vector.end());
	imprimir_variables(vector);



	std::vector<char> size;
	std::cout << "Max_size int: " << size.max_size() << '\n';
	// std::cout << sizeof(ft::iterator_traits<ft::vector<int>::iterator>::iterator_category);

}
