#include "DiamondTrap.hpp"

#include <iostream>

int main(void)
{
	std::cout << "== DiamondTrap basics ==" << std::endl;
	DiamondTrap diamond("卍ULTIMATE YUUTA卍");
	diamond.printStatus();
	diamond.whoAmI();
	diamond.attack("enemy1");
	diamond.guardGate();
	diamond.highFivesGuys();
	diamond.takeDamage(42);
	diamond.beRepaired(10);
	diamond.printStatus();

	std::cout << std::endl << "== Copy and assignment ==" << std::endl;
	DiamondTrap copy(diamond);
	DiamondTrap assigned;
	assigned = diamond;
	copy.whoAmI();
	assigned.attack("enemy2");
	assigned.printStatus();

	std::cout << std::endl << "== Destructor ==" << std::endl;

	return 0;
}
