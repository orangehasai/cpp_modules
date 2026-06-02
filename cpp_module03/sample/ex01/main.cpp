#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

#include <iostream>

int main(void)
{
	std::cout << "== Base class ==" << std::endl;
	ClapTrap basic("Basic");
	basic.attack("cardboard target");
	basic.printStatus();

	std::cout << std::endl << "== Derived class ==" << std::endl;
	{
		ScavTrap serena("Serena");
		serena.printStatus();
		serena.attack("intruder");
		serena.guardGate();
		serena.takeDamage(30);
		serena.beRepaired(10);
		serena.printStatus();
	}

	std::cout << std::endl << "== Orthodox Canonical Form ==" << std::endl;
	ScavTrap original("Checkpoint");
	ScavTrap clone(original);
	ScavTrap assigned;
	assigned = original;
	clone.guardGate();
	assigned.attack("late visitor");

	return 0;
}
