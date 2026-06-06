#ifndef AMATERIA_HPP
#define AMATERIA_HPP

#include <string>

class ICharacter;

class AMateria
{
  public:
	AMateria(std::string const &type);
	AMateria(const AMateria &other);
	AMateria &operator=(const AMateria &other);
	virtual ~AMateria();

	std::string const &getType(void) const;
	unsigned int getXP(void) const;

	virtual AMateria *clone(void) const = 0;
	virtual void use(ICharacter &target);

  protected:
	std::string _type;

  private:
	unsigned int _xp;
};

#endif
