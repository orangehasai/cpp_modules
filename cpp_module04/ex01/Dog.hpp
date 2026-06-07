#ifndef DOG_HPP
#define DOG_HPP

#include <string>
#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public Animal
{
  public:
	Dog();
	Dog(const std::string &type);
	Dog(const Dog &other);
	Dog &operator=(const Dog &other);
	virtual ~Dog();

	void setIdea(int index, const std::string &idea);
	std::string getIdea(int index) const;
	virtual void makeSound() const;

  private:
	Brain *_brain;
};

#endif
