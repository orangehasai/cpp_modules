#include "Dog.hpp"
#include <iostream>

Dog::Dog() : Animal("Dog")
{
	std::cout << "Dog: default constructor called" << std::endl;
}

Dog::Dog(const std::string &type) : Animal(type)
{
	std::cout << "Dog: constructor called" << std::endl;
}

Dog::Dog(const Dog &other) : Animal(other.type)
{
	std::cout << "Dog: copy constructor called" << std::endl;
}

Dog &Dog::operator=(const Dog &other)
{
	std::cout << "Dog: copy assignment constructor called" << std::endl;
	if (this != &other)
	{
		Animal::operator=(other);
		this->type = other.type;
	}
	return *this;
}

Dog::~Dog()
{
	std::cout << "Dog: destructor called" << std::endl;
}

void Dog::makeSound() const
{
	std::cout << "Dog: Woof woof" << std::endl;
}
