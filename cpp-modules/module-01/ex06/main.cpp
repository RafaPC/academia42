#include <string>
#include <iostream>
#include "Karen.hpp"

int main(int argc, char const *argv[])
{
	if (argc == 2)
	{
		Karen karen;
		karen.filter(argv[1]);
	}
	return 0;
}
