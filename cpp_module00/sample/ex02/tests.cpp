#include "Account.hpp"

int	main(void)
{
	const int	initialDeposits[] = {42, 54, 957, 432, 1234, 0, 754, 16576};
	const int	deposits[] = {5, 765, 564, 2, 87, 23, 9, 20};
	const int	withdrawals[] = {321, 34, 657, 4, 76, 275, 657, 7654};
	const int	accountCount = sizeof(initialDeposits) / sizeof(initialDeposits[0]);
	Account		*accounts[accountCount];

	for (int i = 0; i < accountCount; ++i)
		accounts[i] = new Account(initialDeposits[i]);
	Account::displayAccountsInfos();
	for (int i = 0; i < accountCount; ++i)
		accounts[i]->displayStatus();
	for (int i = 0; i < accountCount; ++i)
		accounts[i]->makeDeposit(deposits[i]);
	Account::displayAccountsInfos();
	for (int i = 0; i < accountCount; ++i)
		accounts[i]->displayStatus();
	for (int i = 0; i < accountCount; ++i)
		accounts[i]->makeWithdrawal(withdrawals[i]);
	Account::displayAccountsInfos();
	for (int i = 0; i < accountCount; ++i)
		accounts[i]->displayStatus();
	for (int i = 0; i < accountCount; ++i)
		delete accounts[i];
	return (0);
}
