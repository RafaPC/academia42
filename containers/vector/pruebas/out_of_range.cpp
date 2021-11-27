#include <limits>
#include <iostream>
#include <vector>
using namespace std;
#include <memory>
#include <exception>


int main(int argc, char const *argv[])
{
	vector<int> test(2);

	try
	{
		int x = test.at(1000);

		x = 23;
		cout << "Numero: " << x << '\n';
		cout << test[0] << test[1] << test[2] << endl; 
		cout << test[1000] << endl;
	}
	catch( const out_of_range &ex)
	{
		cout << ex.what();
	}

	return 0;
}
