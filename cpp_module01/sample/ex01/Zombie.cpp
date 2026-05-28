#include "Zombie.hpp"

#include <iostream>

Zombie::Zombie(void) : name("(unnamed)")
{
}

Zombie::~Zombie(void)
{
	std::cout << name << " is destroyed." << std::endl;
}

void Zombie::setName(const std::string &name)
{
	this->name = name;
}

void Zombie::announce(void) const
{
	std::cout << name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
