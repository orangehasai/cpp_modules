#include "Harl.hpp"

#include <iostream>

void Harl::debug(void)
{
	std::cout << "[ DEBUG ]" << std::endl;
	std::cout
		<< "I love having extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger. I really do!"
		<< std::endl;
}

void Harl::info(void)
{
	std::cout << "[ INFO ]" << std::endl;
	std::cout
		<< "I cannot believe adding extra bacon costs more money. You didn't put enough bacon in my burger!"
		<< std::endl;
	std::cout << "If you did, I wouldn't be asking for more!" << std::endl;
}

void Harl::warning(void)
{
	std::cout << "[ WARNING ]" << std::endl;
	std::cout
		<< "I think I deserve to have some extra bacon for free. I've been coming for years,"
		<< std::endl;
	std::cout << "whereas you started working here just last month." << std::endl;
}

void Harl::error(void)
{
	std::cout << "[ ERROR ]" << std::endl;
	std::cout << "This is unacceptable! I want to speak to the manager now."
			  << std::endl;
}

void Harl::complain(const std::string &level)
{
	const std::string levels[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};
	const ComplaintHandler handlers[4] = {
		&Harl::debug,
		&Harl::info,
		&Harl::warning,
		&Harl::error
	};

	for (int i = 0; i < 4; ++i)
	{
		if (levels[i] == level)
		{
			(this->*handlers[i])();
			return;
		}
	}
	std::cout << "Unknown complaint level." << std::endl;
}
