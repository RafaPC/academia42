#include "mutantstack.hpp"
#include <iostream>
#include <list>

int main( void )
{
	// MUTANTSTACK TESTS
	std::cout << "MUTANTSTACKT TESTS:\n\n";
	MutantStack<int> mstack;
	mstack.push(5);
	mstack.push(17);
	std::cout << "Mutantstack top element: " << mstack.top() << std::endl;
	mstack.pop();
	std::cout << "Mutantstack size: " << mstack.size() << std::endl;
	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	mstack.push(0);
	MutantStack<int>::iterator it = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();
	++it;
	--it;

	// CREATING STACK FROM MUTANTSTACK
	std::stack<int> normal_stack(mstack);

	// CREATING MUTANTSTACK COPY
	MutantStack<int> copy_mstack(mstack);
	copy_mstack.pop();
	copy_mstack.push(10);
	MutantStack<int>::iterator copy_it = copy_mstack.begin();
	MutantStack<int>::iterator copy_ite = copy_mstack.end();
	std::cout << "\nMUTANTSTACK CONTENT:\n";
	while (it != ite)
	{
		std::cout << *it << std::endl;
		++it;
	}
	std::cout << "\nMUTANTSTACK COPY CONTENT:\n";
	while (copy_it != copy_ite)
	{
		std::cout << *copy_it << std::endl;
		++copy_it;
	}

	// LIST TESTS
	std::cout << "\n\nLIST TESTS:\n\n";
	std::list<int> mylst;
	mylst.push_back(5);
	mylst.push_back(17);
	std::cout << "List last element: " << mylst.back() << '\n';
	mylst.pop_back();
	std::cout << "List size: " << mylst.size() << '\n';
	mylst.push_back(3);
	mylst.push_back(5);
	mylst.push_back(737);
	mylst.push_back(0);
	std::list<int>::iterator iter = mylst.begin();
	std::list<int>::iterator itend = mylst.end();
	++iter;
	--iter;
	while (iter != itend)
	{
		std::cout << *iter << '\n';
		++iter;
	}
	std::list<int> list_2(mylst);
	return (0);
}