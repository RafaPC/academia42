#include "Zombie.hpp"

int main( void )
{
	Zombie *zombies = zombieHorde(5, "Alfonso");
	for (short i = 0; i < 5; i++)
		zombies[i].announce();
	delete[] zombies;
	return (0);
}
