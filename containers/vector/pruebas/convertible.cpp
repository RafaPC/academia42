template < class From, class To >
		struct is_convertible
		{
			static const From x = To();
			static const bool value = true;
		};
template < class T >
		struct is_convertible<T, T>
		{
			static const bool value = false;
		};

#include <iostream>
#include <string>

int main(void)
{
	std::cout << is_convertible<std::string, int>::value;
	return 0;
}
