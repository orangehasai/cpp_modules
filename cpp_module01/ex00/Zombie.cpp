#include "Zombie.hpp"
#include <iostream>

Zombie::Zombie(const std::string name) : name(name)
{
	std::cout << name << " created." << std::endl;
}

Zombie::~Zombie(void)
{
	std::cout << name << " is destroyed." << std::endl;
}

void Zombie::announce()
{
	std::cout << name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
