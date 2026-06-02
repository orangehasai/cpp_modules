#include "ClapTrap.hpp"

#include <iostream>

static void spendAllEnergy(ClapTrap &robot)
{
	int i;

	for (i = 0; i < 11; ++i)
	{
		robot.attack("practice wall");
	}
}

int main(void)
{
	std::cout << "== Basic behavior ==" << std::endl;
	ClapTrap clap("CL4P-TP");
	clap.printStatus();
	clap.attack("training dummy");
	clap.takeDamage(3);
	clap.beRepaired(2);
	clap.printStatus();
	clap.takeDamage(42);
	clap.attack("ghost target");
	clap.beRepaired(1);

	std::cout << std::endl << "== Energy exhaustion ==" << std::endl;
	ClapTrap runner("Runner");
	spendAllEnergy(runner);
	runner.beRepaired(1);
	runner.printStatus();

	std::cout << std::endl << "== Orthodox Canonical Form ==" << std::endl;
	ClapTrap copied(runner);
	ClapTrap assigned;
	assigned = clap;
	copied.printStatus();
	assigned.printStatus();

	return 0;
}
