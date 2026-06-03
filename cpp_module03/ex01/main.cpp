#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

#include <iostream>

int main(void)
{
	std::cout << "== Base class ==" << std::endl;
	ClapTrap clap("卍YUUTA卍");
	clap.attack("enemy1");
	clap.printStatus();

	std::cout << std::endl << "== Derived class ==" << std::endl;
	ScavTrap Scav("卍YUUTA χ卍");
	Scav.printStatus();
	Scav.attack("enemy χ");
	Scav.guardGate();
	Scav.takeDamage(30);
	Scav.beRepaired(10);
	Scav.printStatus();

	std::cout << std::endl << "== Orthodox Canonical Form ==" << std::endl;
	ScavTrap original("卍YUUTA2卍");
	ScavTrap copied(original);
	ScavTrap assigned;
	assigned = original;

	std::cout << std::endl << "== Destructor ==" << std::endl;

	return 0;
}
