#include "Cat.hpp"
#include <iostream>

Cat::Cat() : Animal("Cat"), _brain(new Brain())
{
	std::cout << "Cat: default constructor called" << std::endl;
}

Cat::Cat(const std::string &type) : Animal(type), _brain(new Brain())
{
	std::cout << "Cat: constructor called" << std::endl;
}

Cat::Cat(const Cat &other) : Animal(other.type), _brain(new Brain(*other._brain))
{
	std::cout << "Cat: copy constructor called" << std::endl;
}

Cat &Cat::operator=(const Cat &other)
{
	std::cout << "Cat: copy assignment constructor called" << std::endl;
	if (this != &other)
	{
		Animal::operator=(other);
		*this->_brain = *other._brain;
	}
	return *this;
}

Cat::~Cat()
{
	delete _brain;
	std::cout << "Cat: destructor called" << std::endl;
}

void Cat::makeSound() const
{
	std::cout << "Cat: meow meow" << std::endl;
}

void Cat::setIdea(int index, const std::string &idea)
{
	_brain->setIdea(index, idea);
}

std::string Cat::getIdea(int index) const
{
	return _brain->getIdea(index);
}
