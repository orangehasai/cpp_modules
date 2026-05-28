#include "Zombie.hpp"

#include <iostream>

int main(void)
{
	std::cout << "1. Stack allocation" << std::endl;
	randomChump("Stacky");

	std::cout << std::endl;
	std::cout << "2. Heap allocation" << std::endl;
	Zombie *heapZombie = newZombie("Heapy");
	heapZombie->announce();
	delete heapZombie;

	return 0;
}
