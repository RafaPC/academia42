#include "map.hpp"
#include <string>
#include <iostream>
#include <map>

int main(void)
{
    ft::map<int, int> mapa;

    mapa[5] = 55;
    mapa[3] = 33;
    mapa[2] = 22;
    mapa[27] = 2727;
    mapa[69] = 6969;
    mapa[7] = 77;
    std::cout << mapa[7] << '\n';
	ft::map<int, int>::iterator iterador = mapa.begin();
	ft::map<int, int>::iterator end = mapa.end();
	
	for (; iterador != end; ++iterador)
	{
		std::cout << iterador->first << ": " << iterador->second << '\n';
	}
	// for (int i = 0; i < 6; i++)
	// {
	// 	std::cout << iterador->first << ": " << iterador->second << '\n';
	// 	++iterador;
	// }
    //TODO: el operador de copia del pair peta porque hace first = other.first pero first es tipo const
	// al hacer que los nodos guarden punteros a pares, no se copian pares, solo se construyen y destruyen
    return 0;
	// std::map<int, int>::iterator
}


    //             5
    //     3				27
    // 2				7		69