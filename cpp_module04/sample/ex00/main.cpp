#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

#include <iostream>

static void printSection(const std::string &title)
{
	std::cout << std::endl << "== " << title << " ==" << std::endl;
}

int main(void)
{
	printSection("Correct polymorphism");
	const Animal *meta = new Animal();
	const Animal *dog = new Dog();
	const Animal *cat = new Cat();

	std::cout << dog->getType() << std::endl;
	std::cout << cat->getType() << std::endl;
	cat->makeSound();
	dog->makeSound();
	meta->makeSound();

	delete meta;
	delete dog;
	delete cat;

	printSection("Wrong polymorphism");
	const WrongAnimal *wrong = new WrongCat();
	std::cout << wrong->getType() << std::endl;
	wrong->makeSound();
	delete wrong;

	printSection("Copy sanity check");
	Dog basic;
	Dog copy(basic);
	Cat assigned;
	assigned = Cat();
	copy.makeSound();
	assigned.makeSound();
	return 0;
}
