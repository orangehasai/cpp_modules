#ifndef DOG_HPP
#define DOG_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public Animal
{
  public:
	Dog();
	Dog(const Dog &other);
	Dog &operator=(const Dog &other);
	virtual ~Dog();

	virtual void makeSound(void) const;
	void setIdea(int index, const std::string &idea);
	std::string getIdea(int index) const;

  private:
	Brain *_brain;
};

#endif
