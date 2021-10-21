#include <iostream>
#include <string>
#include "whatever.hpp"

bool	Example::operator >( Example &other )	const { return (number > other.number); }
bool	Example::operator <( Example &other )	const { return (number < other.number); }
std::ostream &operator<<(std::ostream &os, Example const &a) { os << a.number; return (os); }

int main( void ) {
	int a = 2;
	int b = 3;
	::swap( a, b );
	std::cout << "a = " << a << ", b = " << b << '\n';
	std::cout << "min( a, b ) = " << ::min( a, b ) << '\n';
	std::cout << "max( a, b ) = " << ::max( a, b ) << '\n';
	std::string c = "chaine1";
	std::string d = "chaine2";
	::swap(c, d);
	std::cout << "c = " << c << ", d = " << d << '\n';
	std::cout << "min( c, d ) = " << ::min( c, d ) << '\n';
	std::cout << "max( c, d ) = " << ::max( c, d ) << '\n';
	
	std::cout << "\nExamples with objects\n\n";

	Example example1(24);
	Example example2(42);

	std::cout << "Example1: " << example1 << " - Example2: " << example2 << '\n';
	std::cout << "min( example1, example2 ) = " << ::min<Example>( example1, example2 ) << '\n';
	std::cout << "max( example1, example2 ) = " << ::max<Example>( example1, example2 ) << '\n';
	::swap<Example>(example1, example2);
	std::cout << "Swapped variables\nExample1: " << example1 << " - Example2: " << example2 << '\n';


	std::cout << "\nExamples with floats\n\n";
	float float1(24.3465);
	float float2(3.38674);

	std::cout << "float1: " << float1 << " - float2: " << float2 << '\n';
	std::cout << "min( float1, float2 ) = " << ::min<float>( float1, float2 ) << '\n';
	std::cout << "max( float1, float2 ) = " << ::max<float>( float1, float2 ) << '\n';
	::swap<float>(float1, float2);
	std::cout << "Swapped variables\nfloat1: " << float1 << " - float2: " << float2 << '\n';
	return (0);
}