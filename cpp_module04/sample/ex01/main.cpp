#include "Animal.hpp"
#include "Brain.hpp"
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
	const int animalCount = 6;
	const Animal *zoo[animalCount];
	int i;

	printSection("Delete derived objects through Animal pointers");
	i = 0;
	while (i < animalCount)
	{
		if (i < animalCount / 2)
		{
			zoo[i] = new Dog();
		}
		else
		{
			zoo[i] = new Cat();
		}
		++i;
	}
	i = 0;
	while (i < animalCount)
	{
		zoo[i]->makeSound();
		delete zoo[i];
		++i;
	}

	printSection("Deep copy with Dog");
	Dog originalDog;
	originalDog.setIdea(0, "Protect the house");
	originalDog.setIdea(1, "Ask for snacks");
	Dog copiedDog(originalDog);
	originalDog.setIdea(0, "Chase the mail carrier");
	std::cout << "originalDog idea[0]: " << originalDog.getIdea(0) << std::endl;
	std::cout << "copiedDog   idea[0]: " << copiedDog.getIdea(0) << std::endl;
	std::cout << "copiedDog   idea[1]: " << copiedDog.getIdea(1) << std::endl;

	printSection("Deep copy with Cat assignment");
	Cat firstCat;
	Cat secondCat;
	firstCat.setIdea(0, "Sleep on the keyboard");
	secondCat = firstCat;
	firstCat.setIdea(0, "Ignore the human");
	std::cout << "firstCat  idea[0]: " << firstCat.getIdea(0) << std::endl;
	std::cout << "secondCat idea[0]: " << secondCat.getIdea(0) << std::endl;

	printSection("Wrong polymorphism still fails");
	const WrongAnimal *wrong = new WrongCat();
	wrong->makeSound();
	delete wrong;
	return 0;
}
