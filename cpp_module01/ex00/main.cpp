#include "Zombie.hpp"
#include <iostream>

int main()
{
	Zombie *heapZombie;
	std::cout << "1. Stack allocation" << std::endl;
	randomChump("Stacky");

	std::cout << std::endl;
	std::cout << "2. Heap allocation" << std::endl;
	heapZombie = newZombie("heapy");
	heapZombie->announce();
	delete heapZombie;

	return (0);
}
