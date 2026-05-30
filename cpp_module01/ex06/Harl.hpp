#ifndef HARL_HPP
#define HARL_HPP

#include <string>

class Harl
{
  public:
	void complain(const std::string &level);

  private:
	typedef void (Harl::*complainHandler)(void);

	void debug();
	void info();
	void warning();
	void error();
};

#endif
