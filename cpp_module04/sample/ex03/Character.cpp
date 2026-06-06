#include "Character.hpp"
#include "AMateria.hpp"

#include <iostream>

Character::Character(std::string const &name) : _name(name)
{
	initInventory();
	std::cout << "Character constructor called for " << _name << std::endl;
}

Character::Character(const Character &other) : _name(other._name)
{
	initInventory();
	copyInventory(other);
	std::cout << "Character copy constructor called for " << _name << std::endl;
}

Character &Character::operator=(const Character &other)
{
	if (this != &other)
	{
		clearInventory();
		_name = other._name;
		copyInventory(other);
	}
	std::cout << "Character copy assignment operator called for " << _name
		<< std::endl;
	return *this;
}

Character::~Character()
{
	clearInventory();
	std::cout << "Character destructor called for " << _name << std::endl;
}

std::string const &Character::getName(void) const
{
	return _name;
}

void Character::equip(AMateria *m)
{
	int i;

	if (m == 0 || alreadyEquipped(m))
	{
		return;
	}
	i = 0;
	while (i < 4)
	{
		if (_inventory[i] == 0)
		{
			_inventory[i] = m;
			return;
		}
		++i;
	}
}

void Character::unequip(int idx)
{
	if (!isValidIndex(idx) || _inventory[idx] == 0)
	{
		return;
	}
	_inventory[idx] = 0;
}

void Character::use(int idx, ICharacter &target)
{
	if (!isValidIndex(idx) || _inventory[idx] == 0)
	{
		return;
	}
	_inventory[idx]->use(target);
}

void Character::initInventory(void)
{
	int i;

	i = 0;
	while (i < 4)
	{
		_inventory[i] = 0;
		++i;
	}
}

void Character::clearInventory(void)
{
	int i;

	i = 0;
	while (i < 4)
	{
		delete _inventory[i];
		_inventory[i] = 0;
		++i;
	}
}

void Character::copyInventory(const Character &other)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (other._inventory[i] != 0)
		{
			_inventory[i] = other._inventory[i]->clone();
		}
		else
		{
			_inventory[i] = 0;
		}
		++i;
	}
}

bool Character::isValidIndex(int idx) const
{
	return idx >= 0 && idx < 4;
}

bool Character::alreadyEquipped(AMateria *materia) const
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (_inventory[i] == materia)
		{
			return true;
		}
		++i;
	}
	return false;
}
