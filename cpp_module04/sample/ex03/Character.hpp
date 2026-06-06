#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "ICharacter.hpp"

class AMateria;

class Character : public ICharacter
{
  public:
	Character(std::string const &name);
	Character(const Character &other);
	Character &operator=(const Character &other);
	virtual ~Character();

	virtual std::string const &getName(void) const;
	virtual void equip(AMateria *m);
	virtual void unequip(int idx);
	virtual void use(int idx, ICharacter &target);

  private:
	std::string _name;
	AMateria *_inventory[4];

	void initInventory(void);
	void clearInventory(void);
	void copyInventory(const Character &other);
	bool isValidIndex(int idx) const;
	bool alreadyEquipped(AMateria *materia) const;
};

#endif
