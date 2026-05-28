#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <string>

class Zombie
{
  public:
	Zombie(void);
	~Zombie(void);

	void setName(const std::string &name);
	void announce(void) const;

  private:
	std::string name;
};

Zombie *zombieHorde(int N, const std::string &name);

#endif
