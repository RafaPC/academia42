#include <iostream>
#include <stdint.h>

typedef struct s_Data
{
}				Data;


uintptr_t serialize(Data *ptr);
Data *deserialize(uintptr_t raw);

int main( void )
{
	Data data;

	if (deserialize(serialize(&data)) == &data)
		std::cout << "It works!\n";
	else
		std::cout << "No worky :(\n";
	return 0;
}

uintptr_t serialize(Data *ptr)
{
	uintptr_t	uint_var = reinterpret_cast<uintptr_t>(ptr);
	return (uint_var);
}

Data *deserialize(uintptr_t raw)
{
	Data	*data = reinterpret_cast<Data*>(raw);
	return (data);
}
