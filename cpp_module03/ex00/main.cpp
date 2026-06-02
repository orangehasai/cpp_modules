#include "ClapTrap.hpp"

#include <iostream>

static void spendAllEnergy(ClapTrap &robot)
{
	int i;

	for (i = 0; i < 11; ++i)
	{
		robot.attack("void");
	}
}

int main(void)
{
	std::cout << "== Basic behavior ==" << std::endl;
	ClapTrap clap("卍YUUTA卍");
	clap.printStatus();
	clap.attack("enemy1");
	clap.takeDamage(3);
	clap.beRepaired(2);
	clap.printStatus();
	clap.takeDamage(42);
	clap.attack("enemy2");
	clap.beRepaired(1);

	std::cout << std::endl << "== Energy exhaustion ==" << std::endl;
	ClapTrap claper("卍YUUT2卍");
	spendAllEnergy(claper);
	claper.beRepaired(1);
	claper.printStatus();

	std::cout << std::endl << "== Orthodox Canonical Form ==" << std::endl;
	ClapTrap copied(claper);
	ClapTrap assigned;
	assigned = clap;
	copied.printStatus();
	assigned.printStatus();

	return 0;
}
