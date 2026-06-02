#include "DiamondTrap.hpp"

#include <iostream>

int main(void)
{
	std::cout << "== DiamondTrap basics ==" << std::endl;
	DiamondTrap diamond("Gemini");
	diamond.printStatus();
	diamond.whoAmI();
	diamond.attack("raid boss");
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
	assigned.attack("second raid boss");
	assigned.printStatus();

	return 0;
}
