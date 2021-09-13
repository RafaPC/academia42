#include "Zombie.hpp"

Zombie* zombieHorde( int N, std::string name )
{
	Zombie *zombies = new Zombie[N];
	for (short i = 0; i < N; i++)
		zombies[i].setName(name + std::to_string(i));
	return (zombies);
}