#include <cstdlib>
#include <time.h>
#include <iostream>

class Base {public: virtual ~Base(){}};
class A : public Base {};
class B : public Base {};
class C : public Base {};

Base	*generate(void);
void	identify(Base *p);
void identify(Base& p);

int main( void )
{
	srand(time(NULL));

	Base	*base = generate();
	identify(base);
	identify(*base);
	delete base;
	return (0);
}

Base	*generate(void)
{
	int	chance = rand() % 3;

	if (chance == 0)
	{
		std::cout << "Derived class A was created\n";
		return (new A);
	}
	else if (chance == 1)
	{
		std::cout << "Derived class B was created\n";
		return (new B);
	}
	else
	{
		std::cout << "Derived class C was created\n";
		return (new C);
	}
}

void	identify(Base *p)
{
	if (dynamic_cast<A *>(p))
		std::cout << "A\n";
	else if (dynamic_cast<B *>(p))
		std::cout << "B\n";
	else if (dynamic_cast<C *>(p))
		std::cout << "C\n";
}

void identify(Base& p)
{
	try
	{
		A a = dynamic_cast<A &>(p);
		std::cout << "A\n";
		return ;
	}
	catch (const std::exception &e)
	{
	}

	try
	{
		B b = dynamic_cast<B &>(p);
		std::cout << "B\n";
		return ;
	}
	catch (const std::exception &e)
	{
	}

	try
	{
		C c = dynamic_cast<C &>(p);
		std::cout << "C\n";
		return ;
	}
	catch (const std::exception &e)
	{
	}
}
