#include "Zombie.hpp"

int main(void)
{
	Zombie *zombie1 = newZombie("zombie_1");
	zombie1->announce();
	randomChump("zombie_2");
	delete zombie1;
	return (0);
}
