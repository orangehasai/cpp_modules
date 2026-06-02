#include "ClapTrap.hpp"
#include "FragTrap.hpp"
#include "ScavTrap.hpp"

#include <iostream>

int main(void)
{
	std::cout << "== ClapTrap ==" << std::endl;
	ClapTrap base("Base");
	base.attack("paper enemy");
	base.printStatus();

	std::cout << std::endl << "== ScavTrap ==" << std::endl;
	ScavTrap guard("Watchdog");
	guard.attack("gate crasher");
	guard.guardGate();
	guard.printStatus();

	std::cout << std::endl << "== FragTrap ==" << std::endl;
	FragTrap frag("Sparkles");
	frag.printStatus();
	frag.attack("boss");
	frag.takeDamage(70);
	frag.beRepaired(40);
	frag.highFivesGuys();
	frag.printStatus();

	std::cout << std::endl << "== Orthodox Canonical Form ==" << std::endl;
	FragTrap copy(frag);
	FragTrap assigned;
	assigned = frag;
	copy.highFivesGuys();
	assigned.attack("second boss");

	return 0;
}
