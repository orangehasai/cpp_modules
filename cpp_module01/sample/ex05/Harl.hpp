#ifndef HARL_HPP
#define HARL_HPP

#include <string>

class Harl
{
  public:
	void complain(const std::string &level);

  private:
	typedef void (Harl::*ComplaintHandler)(void);

	void debug(void);
	void info(void);
	void warning(void);
	void error(void);
};

#endif
