#include "ClapTrap.hpp"
#include "FragTrap.hpp"

#include <iostream>

int main(void)
{
	std::cout << "== Base class ==" << std::endl;
	ClapTrap clap("卍YUUTA卍");
	clap.attack("enemy1");
	clap.printStatus();

	std::cout << std::endl << "== Derived class ==" << std::endl;
	FragTrap frag("卍YUUTA χ卍");
	frag.printStatus();
	frag.attack("enemy χ");
	frag.highFivesGuys();
	frag.takeDamage(30);
	frag.beRepaired(10);
	frag.printStatus();

	std::cout << std::endl << "== Orthodox Canonical Form ==" << std::endl;
	FragTrap original("卍YUUTA2卍");
	FragTrap copied(original);
	FragTrap assigned;
	assigned = original;

	std::cout << std::endl << "== Destructor ==" << std::endl;

	return 0;
}
