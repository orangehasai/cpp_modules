#include "Animal.hpp"
#include "Brain.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

#include <iostream>

int main(void)
{
	const int animalCount = 3;
	const Animal *zoo[animalCount];

	std::cout << "== Abstract Animal through polymorphic pointers ==" << std::endl;
	for (int i = 0; i < animalCount; ++i)
	{
		if (i < animalCount / 2)
			zoo[i] = new Dog();
		else
			zoo[i] = new Cat();
	}
	for (int i = 0; i < animalCount; ++i)
	{
		std::cout << "animal " << "[" << i << "] -> ";
		zoo[i]->makeSound();
	}

	std::cout << "== destruct ==" << std::endl;
	for (int i = 0; i < animalCount; ++i)
		delete zoo[i];

	std::cout << "== Deep copy with Dog ==" << std::endl;
	Dog originalDog;
	originalDog.setIdea(0, "OTE");
	originalDog.setIdea(1, "OSUWARI");
	Dog copiedDog(originalDog);
	originalDog.setIdea(0, "OSANPO");
	std::cout << "originalDog idea[0]: " << originalDog.getIdea(0) << std::endl;
	std::cout << "copiedDog   idea[0]: " << copiedDog.getIdea(0) << std::endl;
	std::cout << "originalDog idea[1]: " << originalDog.getIdea(1) << std::endl;
	std::cout << "copiedDog   idea[1]: " << copiedDog.getIdea(1) << std::endl;

	std::cout << "== Deep copy with Cat assignment ==" << std::endl;
	Cat firstCat;
	Cat secondCat;
	firstCat.setIdea(0, "NYAN");
	secondCat = firstCat;
	firstCat.setIdea(0, "MEOW");
	std::cout << "firstCat  idea[0]: " << firstCat.getIdea(0) << std::endl;
	std::cout << "secondCat idea[0]: " << secondCat.getIdea(0) << std::endl;

	std::cout << "== destruct ==" << std::endl;

	return 0;
}
