#include "HumanB.hpp"
#include <iostream>

HumanB::HumanB(const std::string name) : _name(name), _weapon(0)
{
}

void HumanB::setWeapon(Weapon &weapon)
{
	_weapon = &weapon;
}

void HumanB::attack() const
{
	if (_weapon == 0)
	{
		std::cout << _name << " has no weapon." << std::endl;
		return;
	}
	std::cout << _name << "  attacks with their  " << _weapon->getType() << std::endl;
}
