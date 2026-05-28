#include "Zombie.hpp"
#include <iostream>

Zombie::Zombie() : name("")
{
	std::cout << " created." << std::endl;
}

void Zombie::setName(const std::string &name)
{
	this->name = name;
}

Zombie::~Zombie(void)
{
	if (name != "")
		std::cout << name;
	std::cout << " is destroyed." << std::endl;
}

void Zombie::announce()
{
	if (name != "")
		std::cout << name << ": BraiiiiiiinnnzzzZ..." << std::endl;
	else
		std::cout << "The zombie is looking at me as if it wants me to give it a name!"
				  << std::endl;
}
