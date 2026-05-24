#include "Account.hpp"
#include <ctime>
#include <iomanip>
#include <iostream>

int	Account::_nbAccounts = 0;
int	Account::_totalAmount = 0;
int	Account::_totalNbDeposits = 0;
int	Account::_totalNbWithdrawals = 0;

int	Account::getNbAccounts(void)
{
	return (_nbAccounts);
}

int	Account::getTotalAmount(void)
{
	return (_totalAmount);
}

int	Account::getNbDeposits(void)
{
	return (_totalNbDeposits);
}

int	Account::getNbWithdrawals(void)
{
	return (_totalNbWithdrawals);
}

void	Account::_displayTimestamp(void)
{
	std::time_t	rawTime;
	std::tm		*currentTime;

	std::time(&rawTime);
	currentTime = std::localtime(&rawTime);
	if (currentTime == 0)
	{
		std::cout << "[19700101_000000] ";
		return ;
	}
	std::cout << "[";
	std::cout << std::setfill('0') << std::setw(4)
		<< currentTime->tm_year + 1900;
	std::cout << std::setw(2) << currentTime->tm_mon + 1;
	std::cout << std::setw(2) << currentTime->tm_mday << "_";
	std::cout << std::setw(2) << currentTime->tm_hour;
	std::cout << std::setw(2) << currentTime->tm_min;
	std::cout << std::setw(2) << currentTime->tm_sec;
	std::cout << "] ";
	std::cout << std::setfill(' ');
}

void	Account::displayAccountsInfos(void)
{
	_displayTimestamp();
	std::cout << "accounts:" << getNbAccounts()
		<< ";total:" << getTotalAmount()
		<< ";deposits:" << getNbDeposits()
		<< ";withdrawals:" << getNbWithdrawals() << std::endl;
}

Account::Account(int initial_deposit)
	: _accountIndex(_nbAccounts), _amount(initial_deposit),
	  _nbDeposits(0), _nbWithdrawals(0)
{
	++_nbAccounts;
	_totalAmount += initial_deposit;
	_displayTimestamp();
	std::cout << "index:" << _accountIndex
		<< ";amount:" << _amount
		<< ";created" << std::endl;
}

Account::~Account(void)
{
	--_nbAccounts;
	_totalAmount -= _amount;
	_displayTimestamp();
	std::cout << "index:" << _accountIndex
		<< ";amount:" << _amount
		<< ";closed" << std::endl;
}

void	Account::makeDeposit(int deposit)
{
	int	previousAmount;

	previousAmount = _amount;
	_amount += deposit;
	++_nbDeposits;
	_totalAmount += deposit;
	++_totalNbDeposits;
	_displayTimestamp();
	std::cout << "index:" << _accountIndex
		<< ";p_amount:" << previousAmount
		<< ";deposit:" << deposit
		<< ";amount:" << _amount
		<< ";nb_deposits:" << _nbDeposits << std::endl;
}

bool	Account::makeWithdrawal(int withdrawal)
{
	int	previousAmount;

	previousAmount = _amount;
	_displayTimestamp();
	std::cout << "index:" << _accountIndex
		<< ";p_amount:" << previousAmount;
	if (withdrawal > previousAmount)
	{
		std::cout << ";withdrawal:refused" << std::endl;
		return (false);
	}
	_amount -= withdrawal;
	++_nbWithdrawals;
	_totalAmount -= withdrawal;
	++_totalNbWithdrawals;
	std::cout << ";withdrawal:" << withdrawal
		<< ";amount:" << _amount
		<< ";nb_withdrawals:" << _nbWithdrawals << std::endl;
	return (true);
}

int	Account::checkAmount(void) const
{
	return (_amount);
}

void	Account::displayStatus(void) const
{
	_displayTimestamp();
	std::cout << "index:" << _accountIndex
		<< ";amount:" << _amount
		<< ";deposits:" << _nbDeposits
		<< ";withdrawals:" << _nbWithdrawals << std::endl;
}
