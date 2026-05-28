#include "Account.hpp"

#include <ctime>
#include <iomanip>
#include <iostream>

namespace
{
const int kMaxTrackedAccounts = 1024;
int g_closedAmounts[kMaxTrackedAccounts];
int g_liveAccounts = 0;
int g_trackedAccounts = 0;

void recordClosedAccount(int accountIndex, int amount)
{
	if (accountIndex < 0 || accountIndex >= kMaxTrackedAccounts)
		return;
	g_closedAmounts[accountIndex] = amount;
	if (accountIndex + 1 > g_trackedAccounts)
		g_trackedAccounts = accountIndex + 1;
}
} // namespace

int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

int Account::getNbAccounts(void)
{
	return (_nbAccounts);
}

int Account::getTotalAmount(void)
{
	return (_totalAmount);
}

int Account::getNbDeposits(void)
{
	return (_totalNbDeposits);
}

int Account::getNbWithdrawals(void)
{
	return (_totalNbWithdrawals);
}

void Account::_displayTimestamp(void)
{
	std::time_t now;
	std::tm *current;

	now = std::time(NULL);
	current = std::localtime(&now);
	std::cout << "[";
	std::cout << (current->tm_year + 1900);
	std::cout << std::setfill('0') << std::setw(2) << (current->tm_mon + 1);
	std::cout << std::setfill('0') << std::setw(2) << current->tm_mday;
	std::cout << "_";
	std::cout << std::setfill('0') << std::setw(2) << current->tm_hour;
	std::cout << std::setfill('0') << std::setw(2) << current->tm_min;
	std::cout << std::setfill('0') << std::setw(2) << current->tm_sec;
	std::cout << "] ";
	std::cout << std::setfill(' ');
}

void Account::displayAccountsInfos(void)
{
	_displayTimestamp();
	std::cout << "accounts:" << getNbAccounts();
	std::cout << ";total:" << getTotalAmount();
	std::cout << ";deposits:" << getNbDeposits();
	std::cout << ";withdrawals:" << getNbWithdrawals() << std::endl;
}

Account::Account(int initial_deposit)
	: _accountIndex(_nbAccounts), _amount(initial_deposit), _nbDeposits(0), _nbWithdrawals(0)
{
	++_nbAccounts;
	_totalAmount += initial_deposit;
	++g_liveAccounts;
	_displayTimestamp();
	std::cout << "index:" << _accountIndex;
	std::cout << ";amount:" << _amount;
	std::cout << ";created" << std::endl;
}

Account::~Account(void)
{
	recordClosedAccount(_accountIndex, _amount);
	--g_liveAccounts;
	if (g_liveAccounts != 0)
		return;
	for (int i = 0; i < g_trackedAccounts; ++i)
	{
		_displayTimestamp();
		std::cout << "index:" << i;
		std::cout << ";amount:" << g_closedAmounts[i];
		std::cout << ";closed" << std::endl;
	}
	g_trackedAccounts = 0;
}

void Account::makeDeposit(int deposit)
{
	_displayTimestamp();
	std::cout << "index:" << _accountIndex;
	std::cout << ";p_amount:" << _amount;
	std::cout << ";deposit:" << deposit;
	_amount += deposit;
	++_nbDeposits;
	_totalAmount += deposit;
	++_totalNbDeposits;
	std::cout << ";amount:" << _amount;
	std::cout << ";nb_deposits:" << _nbDeposits << std::endl;
}

bool Account::makeWithdrawal(int withdrawal)
{
	_displayTimestamp();
	std::cout << "index:" << _accountIndex;
	std::cout << ";p_amount:" << _amount;
	if (withdrawal > _amount)
	{
		std::cout << ";withdrawal:refused" << std::endl;
		return (false);
	}
	std::cout << ";withdrawal:" << withdrawal;
	_amount -= withdrawal;
	++_nbWithdrawals;
	_totalAmount -= withdrawal;
	++_totalNbWithdrawals;
	std::cout << ";amount:" << _amount;
	std::cout << ";nb_withdrawals:" << _nbWithdrawals << std::endl;
	return (true);
}

int Account::checkAmount(void) const
{
	return (_amount);
}

void Account::displayStatus(void) const
{
	_displayTimestamp();
	std::cout << "index:" << _accountIndex;
	std::cout << ";amount:" << checkAmount();
	std::cout << ";deposits:" << _nbDeposits;
	std::cout << ";withdrawals:" << _nbWithdrawals << std::endl;
}
