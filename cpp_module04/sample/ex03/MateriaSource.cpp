#include "MateriaSource.hpp"
#include "AMateria.hpp"

#include <iostream>

MateriaSource::MateriaSource()
{
	initTemplates();
	std::cout << "MateriaSource default constructor called" << std::endl;
}

MateriaSource::MateriaSource(const MateriaSource &other)
{
	initTemplates();
	copyTemplates(other);
	std::cout << "MateriaSource copy constructor called" << std::endl;
}

MateriaSource &MateriaSource::operator=(const MateriaSource &other)
{
	if (this != &other)
	{
		clearTemplates();
		copyTemplates(other);
	}
	std::cout << "MateriaSource copy assignment operator called" << std::endl;
	return *this;
}

MateriaSource::~MateriaSource()
{
	clearTemplates();
	std::cout << "MateriaSource destructor called" << std::endl;
}

void MateriaSource::learnMateria(AMateria *materia)
{
	int i;

	if (materia == 0 || alreadyKnown(materia))
	{
		return;
	}
	i = 0;
	while (i < 4)
	{
		if (_templates[i] == 0)
		{
			_templates[i] = materia;
			return;
		}
		++i;
	}
}

AMateria *MateriaSource::createMateria(std::string const &type)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (_templates[i] != 0 && _templates[i]->getType() == type)
		{
			return _templates[i]->clone();
		}
		++i;
	}
	return 0;
}

void MateriaSource::initTemplates(void)
{
	int i;

	i = 0;
	while (i < 4)
	{
		_templates[i] = 0;
		++i;
	}
}

void MateriaSource::clearTemplates(void)
{
	int i;

	i = 0;
	while (i < 4)
	{
		delete _templates[i];
		_templates[i] = 0;
		++i;
	}
}

void MateriaSource::copyTemplates(const MateriaSource &other)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (other._templates[i] != 0)
		{
			_templates[i] = other._templates[i]->clone();
		}
		else
		{
			_templates[i] = 0;
		}
		++i;
	}
}

bool MateriaSource::alreadyKnown(AMateria *materia) const
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (_templates[i] == materia)
		{
			return true;
		}
		++i;
	}
	return false;
}
