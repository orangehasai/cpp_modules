#include "AMateria.hpp"
#include "Character.hpp"
#include "Cure.hpp"
#include "Ice.hpp"
#include "IMateriaSource.hpp"
#include "MateriaSource.hpp"

#include <iostream>

static void printSection(const std::string &title)
{
	std::cout << std::endl << "== " << title << " ==" << std::endl;
}

int main(void)
{
	printSection("Subject-style basic scenario");
	IMateriaSource *src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());

	Character me("me");
	AMateria *ice = src->createMateria("ice");
	AMateria *cure = src->createMateria("cure");
	me.equip(ice);
	me.equip(cure);

	Character bob("bob");
	me.use(0, bob);
	me.use(1, bob);
	std::cout << "ice XP: " << ice->getXP() << std::endl;
	std::cout << "cure XP: " << cure->getXP() << std::endl;

	printSection("Inventory limits and unknown materia");
	AMateria *third = src->createMateria("ice");
	AMateria *fourth = src->createMateria("cure");
	AMateria *fifth = src->createMateria("ice");
	AMateria *unknown = src->createMateria("fire");
	me.equip(third);
	me.equip(fourth);
	me.equip(fifth);
	me.use(2, bob);
	me.use(3, bob);
	me.use(4, bob);
	if (unknown == 0)
	{
		std::cout << "unknown materia request returned 0" << std::endl;
	}
	delete fifth;

	printSection("Unequip does not delete");
	AMateria *dropped = src->createMateria("ice");
	Character floorTester("floorTester");
	floorTester.equip(dropped);
	floorTester.use(0, bob);
	floorTester.unequip(0);
	floorTester.use(0, bob);
	std::cout << "dropped XP after unequip: " << dropped->getXP() << std::endl;
	delete dropped;

	printSection("Deep copy on assignment");
	Character assigned("assigned");
	{
		Character temporary("temporary");
		AMateria *tempMateria = src->createMateria("cure");
		temporary.equip(tempMateria);
		temporary.use(0, bob);
		assigned = temporary;
	}
	assigned.use(0, bob);

	printSection("Deep copy on copy construction");
	Character copied(me);
	copied.use(0, bob);
	copied.use(1, bob);

	delete src;
	return 0;
}
