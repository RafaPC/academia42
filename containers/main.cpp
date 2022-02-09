#include <iostream>
#include <ctime>
#include <stdio.h>
#include <string>
#include <list>
#include <cstdlib> // random

#ifdef TEST_FT
	#include "vector/vector.hpp"
	#include "map/map.hpp"
	#include "stack/stack.hpp"
	#include "utility.hpp"
	using namespace ft;

#else
	#include <vector>
	#include <stack>
	#include <map>
	#include <deque>
	#include <utility>
	using namespace std;
#endif

template <typename T>
class foo {
	public:
		typedef T	value_type;

		foo(void) : value(), _verbose(false) { };
		foo(value_type src, const bool verbose = false) : value(src), _verbose(verbose) { };
		foo(foo const &src, const bool verbose = false) : value(src.value), _verbose(verbose) { };
		~foo(void) { if (this->_verbose) std::cout << "~foo::foo()\n"; };
		void m(void) { std::cout << "foo::m called [" << this->value << "]\n"; };
		void m(void) const { std::cout << "foo::m const called [" << this->value << "]\n"; };
		foo &operator=(value_type src) { this->value = src; return *this; };
		foo &operator=(foo const &src) {
			if (this->_verbose || src._verbose)
				std::cout << "foo::operator=(foo) CALLED\n";
			this->value = src.value;
			return *this;
		};
		value_type	getValue(void) const { return this->value; };
		void		switchVerbose(void) { this->_verbose = !(this->_verbose); };

		operator value_type(void) const {
			return value_type(this->value);
		}
	private:
		value_type	value;
		bool		_verbose;
};

typedef vector<foo<int> >					vector_stack_type;
typedef stack<foo<int>, vector_stack_type>	stack_type;

template <typename T>
std::ostream	&operator<<(std::ostream &o, foo<T> const &bar) {
	o << bar.getValue();
	return o;
}

template <typename T>
void	print_size_vector(vector<T> const &vct)
{
	const typename vector<T>::size_type size = vct.size();
	const typename vector<T>::size_type capacity = vct.capacity();
	const typename std::string isCapacityOk = (capacity >= size) ? "OK" : "KO";
	// Cannot limit capacity's max value because it's implementation dependent

	std::cout << "size: " << size << '\n';
	std::cout << "capacity: " << isCapacityOk << '\n';
	typename vector<T>::const_iterator it = vct.begin();
	typename vector<T>::const_iterator ite = vct.end();
	std::cout << '\n'<< "Content is:" << '\n';
	for (; it != ite; ++it)
		std::cout << "- " << *it << '\n';
	std::cout << "###############################################" << '\n';
}

template <typename T_STACK>
void	print_size_stack(T_STACK &stck)
{
	std::cout << "size: " << stck.size() << '\n';
	std::cout << '\n' << "Content was:\n";
	while (stck.size() != 0)
	{
		std::cout << "- " << stck.top() << '\n';
		stck.pop();
	}
	std::cout << "###############################################\n";
}

template <typename T_MAP>
void	print_size_map(T_MAP const &mp)
{
	std::cout << "size: " << mp.size() << '\n';
	typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
	std::cout << '\n' << "Content is:\n";
	for (; it != ite; ++it)
		std::cout << "- " << it->first << ' ' << it->second << '\n';
	std::cout << "###############################################\n";
}

void	check_erase(vector<std::string> const &vct,
					vector<std::string>::const_iterator const &it)
{
	static int i = 0;
	std::cout << "[" << i++ << "] " << "erase: " << it - vct.begin() << '\n';
	print_size_vector(vct);
}

template <class T>
void	cmp(const T &lhs, const T &rhs)
{
	static int i = 0;

	std::cout << "############### [" << i++ << "] ###############"  << '\n';
	std::cout << "eq: " << (lhs == rhs) << " | ne: " << (lhs != rhs) << '\n';
	std::cout << "lt: " << (lhs <  rhs) << " | le: " << (lhs <= rhs) << '\n';
	std::cout << "gt: " << (lhs >  rhs) << " | ge: " << (lhs >= rhs) << '\n';
}

template <typename T>
std::string	printPair(const T &iterator)
{
	std::cout << "key: " << iterator->first << " | value: " << iterator->second;
	std::cout << '\n';
	return ("");
}

// VECTOR

void	vector_assign(void)
{
	vector<int> vct(7);
	vector<int> vct_two(4);
	vector<int> vct_three;
	vector<int> vct_four;

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = (vct.size() - i) * 3;
	for (unsigned long int i = 0; i < vct_two.size(); ++i)
		vct_two[i] = (vct_two.size() - i) * 5;
	print_size_vector(vct);
	print_size_vector(vct_two);

	vct_three.assign(vct.begin(), vct.end());
	vct.assign(vct_two.begin(), vct_two.end());
	vct_two.assign(2, 42);
	vct_four.assign(4, 21);

	std::cout << "\t### After assign(): ###\n";

	print_size_vector(vct);
	print_size_vector(vct_two);
	print_size_vector(vct_three);
	print_size_vector(vct_four);

	vct_four.assign(6, 84);
	print_size_vector(vct_four);

	std::cout << "\t### assign() on enough capacity and low size: ###\n";

	vct.assign(5, 53);
	vct_two.assign(vct_three.begin(), vct_three.begin() + 3);

	print_size_vector(vct);
	print_size_vector(vct_two);
}

void	vector_at(void)
{
		vector<int> vct(7);

	for (unsigned long int i = 0; i < vct.size(); ++i)
	{
		vct.at(i) = (vct.size() - i) * 3;
		std::cout << "vct[]: " << vct[i] << '\n';
	}
	print_size_vector(vct);

	vector<int> const vct_c(vct);

	std::cout << "front(): " << vct.front() << " " << vct_c.front() << '\n';
	std::cout << "back(): " << vct.back() << " " <<  vct_c.back() << '\n';

	for (unsigned long int i = 0; i < vct_c.size(); ++i)
		std::cout << "vct_c.at(): " << vct_c.at(i) << '\n';
	try {
		std::cout << vct_c.at(10) << '\n';
	}
	catch (std::out_of_range &e) {
		std::cout << "Catch out_of_range exception!\n";
	}
	catch (std::exception &e) {
		std::cout << "Catch exception: " << e.what() << '\n';
	}
	print_size_vector(vct_c);
}

void	vector_copy_construct(void)
{
	vector<int> vct(5);
	vector<int>::iterator it = vct.begin(), ite = vct.end();

	std::cout << "len: " << (ite - it) << '\n';
	for (; it != ite; ++it)
		*it = (ite - it);

	it = vct.begin();
	vector<int> vct_range(it, --(--ite));
	for (int i = 0; it != ite; ++it)
		*it = ++i * 5;

	it = vct.begin();
	vector<int> vct_copy(vct);
	for (int i = 0; it != ite; ++it)
		*it = ++i * 7;
	vct_copy.push_back(42);
	vct_copy.push_back(21);

	std::cout << "\t-- PART ONE --\n";
	print_size_vector(vct);
	print_size_vector(vct_range);
	print_size_vector(vct_copy);

	vct = vct_copy;
	vct_copy = vct_range;
	vct_range.clear();

	std::cout << "\t-- PART TWO --\n";
	print_size_vector(vct);
	print_size_vector(vct_range);
	print_size_vector(vct_copy);
}

void	vector_bidirect_iterator(void)
{
	std::list<int> lst;
	std::list<int>::iterator lst_it;
	for (int i = 1; i < 5; ++i)
		lst.push_back(i * 3);

	vector<int> vct(lst.begin(), lst.end());
	print_size_vector(vct);

	lst_it = lst.begin();
	for (int i = 1; lst_it != lst.end(); ++i)
		*lst_it++ = i * 5;
	vct.assign(lst.begin(), lst.end());
	print_size_vector(vct);

	vct.insert(vct.end(), lst.rbegin(), lst.rend());
	print_size_vector(vct);
}

void	vector_insert(void)
{
	{
		vector<int> vct(10);
		vector<int> vct2;

		for (unsigned long int i = 0; i < vct.size(); ++i)
			vct[i] = (vct.size() - i) * 3;
		print_size_vector(vct);

		vct2.insert(vct2.end(), 42);
		vct2.insert(vct2.begin(), 2, 21);
		print_size_vector(vct2);

		vct2.insert(vct2.end() - 2, 42);
		print_size_vector(vct2);

		vct2.insert(vct2.end(), 2, 84);
		print_size_vector(vct2);

		vct2.resize(4);
		print_size_vector(vct2);

		vct2.insert(vct2.begin() + 2, vct.begin(), vct.end());
		vct.clear();
		print_size_vector(vct2);

		print_size_vector(vct);
	}
	{
		vector<int> vct(5);
		vector<int> vct2;
		const int cut = 3;

		for (unsigned long int i = 0; i < vct.size(); ++i)
			vct[i] = (vct.size() - i) * 7;
		print_size_vector(vct);

		vct2.insert(vct2.begin(), vct.begin(), vct.begin() + cut);
		print_size_vector(vct2);
		vct2.insert(vct2.begin(), vct.begin() + cut, vct.end());
		print_size_vector(vct2);
		vct2.insert(vct2.end(), vct.begin(), vct.begin() + cut);
		print_size_vector(vct2);

		std::cout << "insert return:\n";

		std::cout << *vct2.insert(vct2.end(), 42) << '\n';
		std::cout << *vct2.insert(vct2.begin() + 5, 84) << '\n';
		std::cout << "----------------------------------------\n";

		print_size_vector(vct2);
	}
}

void	vector_erase(void)
{
	vector<std::string> vct(10);

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = std::string((vct.size() - i), i + 65);
	print_size_vector(vct);

	check_erase(vct, vct.erase(vct.begin() + 2));

	check_erase(vct, vct.erase(vct.begin()));
	check_erase(vct, vct.erase(vct.end() - 1));

	check_erase(vct, vct.erase(vct.begin(), vct.begin() + 3));
	check_erase(vct, vct.erase(vct.end() - 3, vct.end() - 1));

	vct.push_back("Hello");
	vct.push_back("Hi there");
	print_size_vector(vct);
	check_erase(vct, vct.erase(vct.end() - 3, vct.end()));

	vct.push_back("ONE");
	vct.push_back("TWO");
	vct.push_back("THREE");
	vct.push_back("FOUR");
	print_size_vector(vct);
	check_erase(vct, vct.erase(vct.begin(), vct.end()));
}

void	vector_iterator(void)
{
	const int size = 5;
	vector<int> vct(size);
	vector<int>::iterator it = vct.begin();
	vector<int>::const_iterator ite = vct.begin();

	for (int i = 0; i < size; ++i)
		it[i] = (size - i) * 5;
	// prepost_incdec(vct);

	it = it + 5;
	it = 1 + it;
	it = it - 4;
	std::cout << *(it += 2) << '\n';
	std::cout << *(it -= 1) << '\n';

	*(it -= 2) = 42;
	*(it += 2) = 21;

	std::cout << "const_ite +=: " << *(ite += 2) << '\n';
	std::cout << "const_ite -=: " << *(ite -= 2) << '\n';

	std::cout << "(it == const_it): " << (ite == it) << '\n';
	std::cout << "(const_ite - it): " << (ite - it) << '\n';
	std::cout << "(ite + 3 == it): " << (ite + 3 == it) << '\n';

	print_size_vector(vct);
}

void	vector_reverse_iter(void)
{
	const int size = 5;
	vector<int> vct(size);
	vector<int>::iterator it_ = vct.begin();
	vector<int>::reverse_iterator it(it_);

	for (int i = 0; i < size; ++i)
		vct[i] = (i + 1) * 5;
	print_size_vector(vct);

	std::cout << (it_ == it.base()) << '\n';
	std::cout << (it_ == (it + 3).base()) << '\n';

	std::cout << *(it.base() + 1) << '\n';
	std::cout << *(it - 3) << '\n';
	std::cout << *(it - 3).base() << '\n';
	it -= 3;
	std::cout << *it.base() << '\n';

	std::cout << "TEST OFFSET\n";
	std::cout << *(it) << '\n';
	std::cout << *(it).base() << '\n';
	std::cout << *(it - 0) << '\n';
	std::cout << *(it - 0).base() << '\n';
	std::cout << *(it - 1).base() << '\n';
}

void	vector_swap(void)
{
	vector<int> foo(3, 15);
	vector<int> bar(5, 42);
	
	vector<int>::const_iterator it_foo = foo.begin();
	vector<int>::const_iterator it_bar = bar.begin();

	std::cout << "BEFORE SWAP\n";

	std::cout << "foo contains:\n";
	print_size_vector(foo);
	std::cout << "bar contains:\n";
	print_size_vector(bar);

	foo.swap(bar);

	std::cout << "AFTER SWAP\n";

	std::cout << "foo contains:\n";
	print_size_vector(foo);
	std::cout << "bar contains:\n";
	print_size_vector(bar);

	std::cout << "Iterator validity:\n";
	std::cout << (it_foo == bar.begin()) << '\n';
	std::cout << (it_bar == foo.begin()) << '\n';
}

void	vector_push_pop(void)
{
	vector<std::string> vct(8);
	vector<std::string> vct2;
	vector<std::string>::iterator it = vct.begin();

	for (unsigned long int i = 0; i < vct.size(); ++i)
		it[i] = std::string((vct.size() - i), i + 65);
	print_size_vector(vct);

	std::cout << "push_back():\n\n";

	vct.push_back("One long string");
	vct2.push_back("Another long string");

	print_size_vector(vct);
	print_size_vector(vct2);

	vct.pop_back();
	vct2.pop_back();

	print_size_vector(vct);
	print_size_vector(vct2);
}

void	vector_relational_operator(void)
{
	vector<int> vct(4);
	vector<int> vct2(4);

	cmp(vct, vct);  // 0
	cmp(vct, vct2); // 1

	vct2.resize(10);

	cmp(vct, vct2); // 2
	cmp(vct2, vct); // 3

	vct[2] = 42;

	cmp(vct, vct2); // 4
	cmp(vct2, vct); // 5

	swap(vct, vct2);

	cmp(vct, vct2); // 6
	cmp(vct2, vct); // 7
}

void	vector_exception(void)
{
	vector<int> vct;

	// trying to reserve more space than maximum
	try
	{
		vct.resize(vct.max_size() + 1);
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << '\n';
	}

	//trying to access element past the end
	try
	{
		vct.at(1);
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
}

void	vector_speed(void)
{
	clock_t init_time = clock();

	srand(1643304846);
	vector<int> vct;

	for (int i = 0; i < 1000000; ++i)
		vct.push_back(i);
	

	float execution_time = static_cast<float>(clock() - init_time)/(float)CLOCKS_PER_SEC;
	printf("Vector execution time: %f s\n", execution_time);
}

// STACK

void	stack_default(void)
{
	stack_type stck;

	std::cout << "empty: " << stck.empty() << '\n';
	std::cout << "size: " << stck.size() << '\n';

	stck.push(41);
	stck.push(29);
	stck.push(10);
	stck.push(42);
	std::cout << "Added some elements\n";

	std::cout << "empty: " << stck.empty() << '\n';
	print_size_stack(stck);
}

void	stack_default_copy(void)
{
	vector_stack_type	ctnr;

	ctnr.push_back(21);
	ctnr.push_back(42);
	ctnr.push_back(1337);
	ctnr.push_back(19);
	ctnr.push_back(0);
	ctnr.push_back(183792);

	stack_type		stck(ctnr);

	std::cout << "empty: " << stck.empty() << '\n';
	std::cout << "size: " << stck.size() << '\n';

	stck.push(1);
	stck.push(2);
	stck.push(3);
	stck.push(4);
	stck.push(5);
	stck.push(6);

	std::cout << "Added some elements\n";

	std::cout << "empty: " << stck.empty() << '\n';
	print_size_stack(stck);
}

void	stack_list(void)
{
	vector_stack_type	ctnr;

	ctnr.push_back(21);
	ctnr.push_back(42);
	ctnr.push_back(1337);
	ctnr.push_back(19);
	ctnr.push_back(0);
	ctnr.push_back(183792);

	stack_type	stck(ctnr);

	std::cout << "empty: " << stck.empty() << '\n';
	std::cout << "size: " << stck.size() << '\n';

	stck.push(1);
	stck.push(2);
	stck.push(3);
	stck.push(4);
	stck.push(5);
	stck.push(6);

	std::cout << "Added some elements\n";

	std::cout << "empty: " << stck.empty() << '\n';
	print_size_stack(stck);
}

void	stack_relational_operator(void)
{
	vector_stack_type	ctnr;

	ctnr.push_back(21);
	ctnr.push_back(42);
	ctnr.push_back(1337);
	ctnr.push_back(19);
	ctnr.push_back(0);
	ctnr.push_back(183792);

	stack_type	stck(ctnr);
	stack_type	stck2(ctnr);

	cmp(stck, stck);  // 0
	cmp(stck, stck2); // 1

	stck2.push(60);
	stck2.push(61);
	stck2.push(62);

	cmp(stck, stck2); // 2
	cmp(stck2, stck); // 3

	stck.push(42);

	cmp(stck, stck2); // 4
	cmp(stck2, stck); // 5

	stck.push(100);

	cmp(stck, stck2); // 6
	cmp(stck2, stck); // 7
}

//MAP
typedef map<int, int>::value_type			int_pair_type;
typedef	map<int, std::string>::value_type	int_string_pair;

void	map_construct(void)
{
	std::list<int_string_pair> lst;
	std::list<int_string_pair>::iterator itlst;

	lst.push_back(int_string_pair(42, "lol"));
	lst.push_back(int_string_pair(50, "mdr"));
	lst.push_back(int_string_pair(35, "funny"));
	lst.push_back(int_string_pair(45, "bunny"));
	lst.push_back(int_string_pair(21, "fizz"));
	lst.push_back(int_string_pair(35, "this key is already inside"));
	lst.push_back(int_string_pair(55, "fuzzy"));
	lst.push_back(int_string_pair(38, "buzz"));
	lst.push_back(int_string_pair(55, "inside too"));

	std::cout << "List contains: " << lst.size() << " elements.\n";
	for (itlst = lst.begin(); itlst != lst.end(); ++itlst)
		printPair(itlst);
	std::cout << "---------------------------------------------\n";

	map<int, std::string> mp(lst.begin(), lst.end());
	lst.clear();

	print_size_map(mp);
}

void	map_relational_operator(void)
{
	map<char, int> mp1;
	map<char, int> mp2;

	mp1['a'] = 2; mp1['b'] = 3; mp1['c'] = 4; mp1['d'] = 5;
	mp2['a'] = 2; mp2['b'] = 3; mp2['c'] = 4; mp2['d'] = 5;

	cmp(mp1, mp1); // 0
	cmp(mp1, mp2); // 1

	mp2['e'] = 6; mp2['f'] = 7; mp2['h'] = 8; mp2['h'] = 9;

	cmp(mp1, mp2); // 2
	cmp(mp2, mp1); // 3

	(++(++mp1.begin()))->second = 42;

	cmp(mp1, mp2); // 4
	cmp(mp2, mp1); // 5

	swap(mp1, mp2);

	cmp(mp1, mp2); // 6
	cmp(mp2, mp1); // 7
}

void	map_copy_construct(void)
{
	std::list<int_pair_type> lst;
	for (unsigned int i = 0; i < 7; ++i)
		lst.push_back(int_pair_type(7 - i, i));

	map<int, int> mp(lst.begin(), lst.end());
	map<int, int>::iterator it = mp.begin(), ite = mp.end();

	map<int, int> mp_range(it, --(--ite));
	for (int i = 0; it != ite; ++it)
		it->second = ++i * 5;

	it = mp.begin(); ite = --(--mp.end());
	map<int, int> mp_copy(mp);
	for (int i = 0; it != ite; ++it)
		it->second = ++i * 7;

	std::cout << "\t-- PART ONE --\n";
	print_size_map(mp);
	print_size_map(mp_range);
	print_size_map(mp_copy);

	mp = mp_copy;
	mp_copy = mp_range;
	mp_range.clear();
	print_size_map(mp);
	print_size_map(mp_range);
	print_size_map(mp_copy);
}

void	map_empty(void)
{
	std::list<int_pair_type> lst;
	for (unsigned int i = 0; i < 7; ++i)
		lst.push_back(int_pair_type('a' + i, 7 - i));

	map<int, int> mp(lst.begin(), lst.end()), mp2;
	map<int, int>::iterator it;

	lst.clear();
	std::cout << "is_empty: " << mp.empty() << '\n';
	print_size_map(mp);

	std::cout << "is_empty: " << mp2.empty() << '\n';
	mp2 = mp;
	std::cout << "is_empty: " << mp2.empty() << '\n';

	it = mp.begin();
	for (unsigned long int i = 3; i < mp.size(); ++i)
		it++->second = i * 7;

	print_size_map(mp);
	print_size_map(mp2);

	mp2.clear();
	std::cout << "is_empty: " << mp2.empty() << '\n';
	print_size_map(mp2);
}

void	map_erase(void)
{
	std::list<int_string_pair> lst;
	for (unsigned int i = 0; i < 8; ++i)
		lst.push_back(int_string_pair(i, std::string((8 - i), i + 65)));
	map<int, std::string> mp(lst.begin(), lst.end());
	// print_size_map(mp);
	mp.erase(++mp.begin());

	mp.erase(mp.begin());
	// displayTree(mp._root_node);
	mp.erase(--mp.end());
	mp.erase(mp.begin(), ++(++(++mp.begin())));
	mp.erase(--(--(--mp.end())), --mp.end());

	mp[10] = "Hello";
	mp[11] = "Hi there";
	print_size_map(mp);
	mp.erase(--(--(--mp.end())), mp.end());

	mp[12] = "ONE";
	mp[13] = "TWO";
	mp[14] = "THREE";
	mp[15] = "FOUR";
	print_size_map(mp);
	mp.erase(mp.begin(), mp.end());
}

void	map_find_count(void)
{
	map<int, std::string> mp;
	map<int, std::string>::iterator last = mp.end();
	mp[12] = "no";
	mp[27] = "bee";
	mp[90] = "8";
	print_size_map(mp);

	std::cout << "\t-- FIND --\n";
	if (mp.find(12) == last)
		std::cout << "map::find(" << 12 << ") returned end()\n";
	if (mp.find(3) == last)
		std::cout << "map::find(" << 3 << ") returned end()\n";
	if (mp.find(90) == last)
		std::cout << "map::find(" << 90 << ") returned end()\n";

	std::cout << "\t-- COUNT --\n";
	std::cout << "map::count(" << 12 << ")\treturned [" << mp.count(12) << "]\n";
	std::cout << "map::count(" << 3 << ")\treturned [" << mp.count(3) << "]\n";
	std::cout << "map::count(" << 90 << ")\treturned [" << mp.count(90) << "]\n";

	mp.find(27)->second = "newly inserted mapped_value";
	print_size_map(mp);

	map<int, std::string> const c_map(mp.begin(), mp.end());
	std::cout << "const map.find(" << 42 << ")->second: [" << c_map.find(12)->second << "]\n";
	std::cout << "const map.count(" << 80 << "): [" << c_map.count(80) << "]\n";
}

void	map_swap(void)
{
	std::list<int_pair_type> lst;

	for (unsigned int i = 0; i < 7; ++i)
		lst.push_back(int_pair_type('a' + i, 7 - i));
	map<int, int> foo(lst.begin(), lst.end());

	lst.clear();
	for (unsigned int i = 0; i < 4; ++i)
		lst.push_back(int_pair_type('z' - i, i * 5));
	map<int, int> bar(lst.begin(), lst.end());

	map<int, int>::const_iterator it_foo = foo.begin();
	map<int, int>::const_iterator it_bar = bar.begin();

	std::cout << "BEFORE SWAP\n";

	std::cout << "foo contains:\n";
	print_size_map(foo);
	std::cout << "bar contains:\n";
	print_size_map(bar);

	foo.swap(bar);

	std::cout << "AFTER SWAP\n";

	std::cout << "foo contains:\n";
	print_size_map(foo);
	std::cout << "bar contains:\n";
	print_size_map(bar);

	std::cout << "Iterator validity:\n";
	std::cout << (it_foo == bar.begin()) << '\n';
	std::cout << (it_bar == foo.begin()) << '\n';
}

void	map_reverse_iterator(void)
{
	std::list<int_pair_type> lst;
	for (unsigned int i = 0; i < 5; ++i)
		lst.push_back(int_pair_type(2.5 - i, (i + 1) * 7));

	map<int, int> mp(lst.begin(), lst.end());
	map<int, int>::reverse_iterator it(mp.rbegin());
	map<int, int>  ::const_reverse_iterator ite(mp.rbegin());
	print_size_map(mp);

	std::cout << "key: " << (++ite)->first << " | value: " << ite->second;
	std::cout << "key: " << (ite++)->first << " | value: " << ite->second;

	std::cout << "key: " << (++it)->first << " | value: " << ite->second;
	std::cout << "key: " << (it++)->first << " | value: " << ite->second;

	std::cout << "key: " << (--ite)->first << " | value: " << ite->second;
	std::cout << "key: " << (ite--)->first << " | value: " << ite->second;

	std::cout << "key: " << (--it)->first << " | value: " << ite->second;
	std::cout << "key: " << (it--)->first << " | value: " << ite->second;
}

template <typename MAP>
void	map_const_bound(const MAP &mp, const int &param)
{
	typedef typename MAP::const_iterator const_iter;
	const_iter ite = mp.end(), it[2];
	pair<const_iter, const_iter> ft_range;

	std::cout << "with key [" << param << "]:\n";
	it[0] = mp.lower_bound(param); it[1] = mp.upper_bound(param);
	ft_range = mp.equal_range(param);
	std::cout << "lower_bound: " << (it[0] == ite ? "end()" : "") << '\n';
	std::cout << "upper_bound: " << (it[1] == ite ? "end()" : "") << '\n';
	std::cout << "equal_range: " << (ft_range.first == it[0] && ft_range.second == it[1]) << '\n';
}

void	map_bounds(void)
{
	std::list<int_pair_type> lst;
	for (unsigned int i = 0; i < 10; ++i)
		lst.push_back(int_pair_type(i + 1, (i + 1) * 3));
	map<int, int> mp(lst.begin(), lst.end());

	map_const_bound(mp, -10);
	map_const_bound(mp, 1);
	map_const_bound(mp, 5);
	map_const_bound(mp, 10);
	map_const_bound(mp, 50);

	print_size_map(mp);
}

void	map_value_compare(void)
{
	map<int, std::string>	mp;
	map<int, std::string>::value_compare value_compare = mp.value_comp();
	map<int, std::string>::iterator it = mp.begin();
	mp[1] = "foo";
	mp[2] = "bar";
	mp[3] = "bar";

	if (value_compare(*it, *(++it)))
		std::cout << "1-foo is less than 2-bar\n";
	if (!value_compare(*it, *(++it)))
		std::cout << "2-bar is not less than 3-bar\n";
}

void	map_speed(void)
{
	clock_t init_time = clock();

	srand(1643304846);
	map<long, int> mapa;

	// Inserting aa lot of values into the map
	for (unsigned int i = 0; i < 100000; ++i)
		mapa.insert(map<long, int>::value_type(random(), i));

	for (map<long, int>::iterator it = mapa.begin(), last = mapa.end(); it != last; ++it)
		std::cout << it->first << ": " << it->second << '\n';

	float execution_time = static_cast<float>(clock() - init_time)/(float)CLOCKS_PER_SEC;
	printf("Map execution time: %f s\n", execution_time);
}

// To call only with my map
// template <typename T>
// void	distance_from_leaves_to_root(T &mapa)
// {
// 	for (typename T::iterator it = mapa.begin(), last = mapa.end(); it != last; ++it)
// 	{
// 		typename T::iterator before_end = --(mapa.end());
// 		ft::rb_tree_node<pair<const typename T::key_type, typename T::mapped_type> > *node = it.base();
// 		if (it == before_end || (node->left == NULL && node->right == NULL))
// 		{
// 			int count = 0;
// 			while (node->parent)
// 			{
// 				if (node->color == true)
// 					++count;
// 				node = node->parent;
// 			}
// 			std::cout << "For " << it->first << ", count " << count << " nodes to root\n";
// 		}
// 	}
// }

int main(void)
{
	// VECTOR
	vector_copy_construct();
	vector_relational_operator();
	vector_assign();
	vector_insert();
	vector_erase();
	vector_bidirect_iterator();
	vector_push_pop();
	vector_at();
	vector_iterator();
	vector_reverse_iter();
	vector_swap();
	vector_exception();
	vector_speed();

	//STACK
	stack_default();
	stack_default_copy();
	stack_list();
	stack_relational_operator();
	stack_relational_operator();

	//MAP
	map_construct();
	map_copy_construct();
	map_empty();
	map_erase();
	map_relational_operator();
	map_find_count();
	map_swap();
	map_reverse_iterator();
	map_bounds();
	map_value_compare();
	map_speed();

	//FIXME: borrar esto
	// map<int, int> mapita;
	// for (int i = 0; i < 20; ++i)
	// {
	// 	mapita[i] = i;
	// 	mapita.displayTree();
	// }
	// distance_from_leaves_to_root(mapita);

	// mapita.erase(++(++(++(++(++mapita.begin())))), mapita.end());
	// mapita.displayTree();
	// distance_from_leaves_to_root(mapita);
}