#include <string>
#include <iostream>

int main(void)
{
	std::string var = "HI THIS IS BRAIN";
	std::string	*var_ptr = &var;
	std::string& var_ref = var;

	std::cout << "String address:\n";
	std::cout << &var << "\n";
	std::cout << var_ptr << "\n";
	std::cout << &var_ref << "\n\n";

	std::cout << "String content:\n";
	std::cout << var << "\n";
	std::cout << *var_ptr << "\n";
	std::cout << var_ref << "\n";
	return (0);
}
