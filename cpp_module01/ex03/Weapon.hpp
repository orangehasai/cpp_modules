#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <string>

class Weapon
{
  public:
	Weapon(const std::string weaponType);
	const std::string &getType() const;
	void setType(const std::string weaponType);

  private:
	std::string type;
};

#endif
