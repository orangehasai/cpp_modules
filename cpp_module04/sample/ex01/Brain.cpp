#include "Brain.hpp"

#include <iostream>

Brain::Brain()
{
	int i;

	i = 0;
	while (i < 100)
	{
		ideas[i] = "(empty)";
		++i;
	}
	std::cout << "Brain default constructor called" << std::endl;
}

Brain::Brain(const Brain &other)
{
	int i;

	i = 0;
	while (i < 100)
	{
		ideas[i] = other.ideas[i];
		++i;
	}
	std::cout << "Brain copy constructor called" << std::endl;
}

Brain &Brain::operator=(const Brain &other)
{
	int i;

	if (this != &other)
	{
		i = 0;
		while (i < 100)
		{
			ideas[i] = other.ideas[i];
			++i;
		}
	}
	std::cout << "Brain copy assignment operator called" << std::endl;
	return *this;
}

Brain::~Brain()
{
	std::cout << "Brain destructor called" << std::endl;
}

void Brain::setIdea(int index, const std::string &idea)
{
	if (index < 0 || index >= 100)
	{
		return;
	}
	ideas[index] = idea;
}

std::string Brain::getIdea(int index) const
{
	if (index < 0 || index >= 100)
	{
		return "";
	}
	return ideas[index];
}
