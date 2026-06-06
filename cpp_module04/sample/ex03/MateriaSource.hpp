#ifndef MATERIASOURCE_HPP
#define MATERIASOURCE_HPP

#include "IMateriaSource.hpp"

class AMateria;

class MateriaSource : public IMateriaSource
{
  public:
	MateriaSource();
	MateriaSource(const MateriaSource &other);
	MateriaSource &operator=(const MateriaSource &other);
	virtual ~MateriaSource();

	virtual void learnMateria(AMateria *materia);
	virtual AMateria *createMateria(std::string const &type);

  private:
	AMateria *_templates[4];

	void initTemplates(void);
	void clearTemplates(void);
	void copyTemplates(const MateriaSource &other);
	bool alreadyKnown(AMateria *materia) const;
};

#endif
