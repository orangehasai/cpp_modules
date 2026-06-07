#include "Dog.hpp"
#include <iostream>

Dog::Dog() : Animal("Dog"), _brain(new Brain())
{
	std::cout << "Dog: default constructor called" << std::endl;
}

Dog::Dog(const std::string &type) : Animal(type), _brain(new Brain())
{
	std::cout << "Dog: constructor called" << std::endl;
}

Dog::Dog(const Dog &other) : Animal(other.type), _brain(new Brain(*other._brain))
{
	std::cout << "Dog: copy constructor called" << std::endl;
}

Dog &Dog::operator=(const Dog &other)
{
	std::cout << "Dog: copy assignment constructor called" << std::endl;
	if (this != &other)
	{
		Animal::operator=(other);
		*this->_brain = *other._brain;
	}
	return *this;
}

Dog::~Dog()
{
	delete _brain;
	std::cout << "Dog: destructor called" << std::endl;
}

void Dog::makeSound() const
{
	std::cout << "Dog: Woof woof" << std::endl;
}

void Dog::setIdea(int index, const std::string &idea)
{
	_brain->setIdea(index, idea);
}

std::string Dog::getIdea(int index) const
{
	return _brain->getIdea(index);
}
