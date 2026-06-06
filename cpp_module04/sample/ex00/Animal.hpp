#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <string>

class Animal
{
  public:
	Animal();
	Animal(const Animal &other);
	Animal &operator=(const Animal &other);
	virtual ~Animal();

	std::string getType(void) const;
	virtual void makeSound(void) const;

  protected:
	std::string type;
};

#endif
