#include "Cat.hpp"
#include <iostream>

Cat::Cat() : Animal("Cat")
{
	std::cout << "Cat: default constructor called" << std::endl;
}

Cat::Cat(const std::string &type) : Animal(type)
{
	std::cout << "Cat: constructor called" << std::endl;
}

Cat::Cat(const Cat &other) : Animal(other.type)
{
	std::cout << "Cat: copy constructor called" << std::endl;
}

Cat &Cat::operator=(const Cat &other)
{
	std::cout << "Cat: copy assignment constructor called" << std::endl;
	if (this != &other)
	{
		Animal::operator=(other);
		this->type = other.type;
	}
	return *this;
}

Cat::~Cat()
{
	std::cout << "Cat: destructor called" << std::endl;
}

void Cat::makeSound() const
{
	std::cout << "Cat: meow meow" << std::endl;
}
