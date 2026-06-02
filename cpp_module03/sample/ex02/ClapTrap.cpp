#include "ClapTrap.hpp"

#include <iostream>

ClapTrap::ClapTrap()
	: _name("anonymous"), _hitPoints(10), _energyPoints(10), _attackDamage(0)
{
	std::cout << "ClapTrap " << _name << " default constructor called"
		<< std::endl;
}

ClapTrap::ClapTrap(const std::string &name)
	: _name(name), _hitPoints(10), _energyPoints(10), _attackDamage(0)
{
	std::cout << "ClapTrap " << _name << " constructor called" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &other)
	: _name(other._name), _hitPoints(other._hitPoints),
	  _energyPoints(other._energyPoints), _attackDamage(other._attackDamage)
{
	std::cout << "ClapTrap " << _name << " copy constructor called"
		<< std::endl;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &other)
{
	if (this != &other)
	{
		_name = other._name;
		_hitPoints = other._hitPoints;
		_energyPoints = other._energyPoints;
		_attackDamage = other._attackDamage;
	}
	std::cout << "ClapTrap " << _name << " copy assignment operator called"
		<< std::endl;
	return *this;
}

ClapTrap::~ClapTrap()
{
	std::cout << "ClapTrap " << _name << " destructor called" << std::endl;
}

bool ClapTrap::canAct(const std::string &action) const
{
	if (_hitPoints == 0)
	{
		std::cout << "ClapTrap " << _name << " can't " << action
			<< " because it has no hit points left." << std::endl;
		return false;
	}
	if (_energyPoints == 0)
	{
		std::cout << "ClapTrap " << _name << " can't " << action
			<< " because it has no energy points left." << std::endl;
		return false;
	}
	return true;
}

void ClapTrap::attack(const std::string &target)
{
	if (!canAct("attack"))
	{
		return;
	}
	--_energyPoints;
	std::cout << "ClapTrap " << _name << " attacks " << target
		<< ", causing " << _attackDamage << " points of damage!" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount)
{
	unsigned int damageTaken;
	unsigned int previousHitPoints;

	if (_hitPoints == 0)
	{
		std::cout << "ClapTrap " << _name
			<< " is already at 0 hit points." << std::endl;
		return;
	}
	damageTaken = amount;
	if (damageTaken > _hitPoints)
	{
		damageTaken = _hitPoints;
	}
	previousHitPoints = _hitPoints;
	_hitPoints -= damageTaken;
	std::cout << "ClapTrap " << _name << " takes " << damageTaken
		<< " points of damage. Hit points: " << previousHitPoints << " -> "
		<< _hitPoints << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount)
{
	if (!canAct("repair itself"))
	{
		return;
	}
	--_energyPoints;
	_hitPoints += amount;
	std::cout << "ClapTrap " << _name << " repairs itself for " << amount
		<< " hit points. Hit points are now " << _hitPoints << std::endl;
}

void ClapTrap::printStatus(void) const
{
	std::cout << "[ClapTrap status] name=" << _name << ", hp=" << _hitPoints
		<< ", energy=" << _energyPoints << ", damage=" << _attackDamage
		<< std::endl;
}
