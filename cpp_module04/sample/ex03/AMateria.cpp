#include "AMateria.hpp"

AMateria::AMateria(std::string const &type) : _type(type), _xp(0)
{
}

AMateria::AMateria(const AMateria &other) : _type(other._type), _xp(other._xp)
{
}

AMateria &AMateria::operator=(const AMateria &other)
{
	if (this != &other)
	{
		_xp = other._xp;
	}
	return *this;
}

AMateria::~AMateria()
{
}

std::string const &AMateria::getType(void) const
{
	return _type;
}

unsigned int AMateria::getXP(void) const
{
	return _xp;
}

void AMateria::use(ICharacter &target)
{
	(void)target;
	_xp += 10;
}
