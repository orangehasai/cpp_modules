#include "Account.hpp"
#include <iostream>
#include <ctime>
#include <iomanip>

int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

int Account::getNbAccounts(void)
{
	return _nbAccounts;
}
int Account::getTotalAmount(void)
{
	return _totalAmount;
}
int Account::getNbDeposits(void)
{
	return _totalNbDeposits;
}
int Account::getNbWithdrawals(void)
{
	return _totalNbWithdrawals;
}

void Account::_displayTimestamp(void)
{
	std::time_t unixNow;
	std::tm *now;

	unixNow = std::time(NULL);
	now = std::localtime(&unixNow);
	std::cout << "[";
	std::cout << (now->tm_year + 1900);
	std::cout << std::setw(2) << std::setfill('0') << (now->tm_mon + 1);
	std::cout << std::setw(2) << std::setfill('0') << now->tm_mday;
	std::cout << "_";
	std::cout << std::setw(2) << std::setfill('0') << now->tm_hour;
	std::cout << std::setw(2) << std::setfill('0') << now->tm_min;
	std::cout << std::setw(2) << std::setfill('0') << now->tm_sec;
	std::cout << "] ";
	std::cout << std::setfill(' ');
}

void Account::displayAccountsInfos(void)
{
	_displayTimestamp();
	std::cout << "accounts:" << _nbAccounts << ";";
	std::cout << "total:" << _totalAmount << ";";
	std::cout << "deposits:" << _totalNbDeposits << ";";
	std::cout << "withdrawals:" << _totalNbWithdrawals << std::endl;
}

Account::Account(int initial_deposit)
	: _accountIndex(_nbAccounts), _amount(initial_deposit), _nbDeposits(0), _nbWithdrawals(0)
{
	_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";";
	std::cout << "amount:" << _amount << ";";
	std::cout << "created" << std::endl;
	++_nbAccounts;
	_totalAmount += _amount;
}

Account::~Account(void)
{
	struct ClosedLogEntry
	{
		int index;
		int amount;
	};

	static ClosedLogEntry *logs = NULL;
	static int destroyedCount = 0;
	static int totalAccounts = 0;

	if (logs == NULL)
	{
		totalAccounts = getNbAccounts();
		logs = new ClosedLogEntry[totalAccounts];
	}
	logs[destroyedCount].index = _accountIndex;
	logs[destroyedCount].amount = _amount;
	++destroyedCount;
	--_nbAccounts;
	_totalAmount -= _amount;
	if (destroyedCount != totalAccounts)
		return;
	while (destroyedCount--)
	{
		_displayTimestamp();
		std::cout << "index:" << logs[destroyedCount].index << ";";
		std::cout << "amount:" << logs[destroyedCount].amount << ";";
		std::cout << "closed" << std::endl;
	}
	delete[] logs;
	logs = NULL;
	destroyedCount = 0;
	totalAccounts = 0;
}

void Account::makeDeposit(int deposit)
{
	_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";";
	std::cout << "p_amount:" << _amount << ";";
	std::cout << "deposit:" << deposit << ";";
	_amount += deposit;
	std::cout << "amount:" << _amount << ";";
	++_nbDeposits;
	std::cout << "nb_deposits:" << _nbDeposits << std::endl;
	_totalAmount += deposit;
	++_totalNbDeposits;
}

bool Account::makeWithdrawal(int withdrawal)
{
	_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";";
	std::cout << "p_amount:" << _amount << ";";
	if (_amount < withdrawal)
	{
		std::cout << "withdrawal:refused" << std::endl;
		return false;
	}
	else
	{
		std::cout << "withdrawal:" << withdrawal << ";";
		_amount -= withdrawal;
		std::cout << "amount:" << _amount << ";";
		++_nbWithdrawals;
		std::cout << "nb_withdrawals:" << _nbWithdrawals << std::endl;
		_totalAmount -= withdrawal;
		++_totalNbWithdrawals;
		return true;
	}
}

int Account::checkAmount(void) const
{
	return _amount;
}

void Account::displayStatus(void) const
{
	_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";";
	std::cout << "amount:" << _amount << ";";
	std::cout << "deposits:" << _nbDeposits << ";";
	std::cout << "withdrawals:" << _nbWithdrawals << std::endl;
}
