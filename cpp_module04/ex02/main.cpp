#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

#include <iostream>

int main()
{
	std::cout << "== Correct polymorphism ==" << std::endl;
	const Animal *meta = new Animal();
	const Animal *dog = new Dog();
	const Animal *cat = new Cat();

	std::cout << dog->getType() << std::endl;
	std::cout << cat->getType() << std::endl;
	cat->makeSound();
	dog->makeSound();
	meta->makeSound();

	std::cout << "== Destruct ==" << std::endl;
	delete meta;
	delete dog;
	delete cat;

	std::cout << "== Wrong polymorphism ==" << std::endl;
	const WrongAnimal *wrong = new WrongCat();
	std::cout << wrong->getType() << std::endl;
	wrong->makeSound();

	std::cout << "== Destruct ==" << std::endl;
	delete wrong;

	std::cout << "== Copy sanity check ==" << std::endl;
	Dog basic;
	Dog copy(basic);
	Cat assigned;
	assigned = Cat();
	copy.makeSound();
	assigned.makeSound();

	std::cout << "== Destruct ==" << std::endl;

	return 0;
}
