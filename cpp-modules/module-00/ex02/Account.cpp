#include <iostream>
#include <ctime>
#include "Account.hpp"

// STATIC VARIABLES
int	Account::_nbAccounts = 0;
int	Account::_totalAmount = 0;
int	Account::_totalNbDeposits = 0;
int	Account::_totalNbWithdrawals = 0;

// STATIC FUNCTIONS
int	Account::getNbAccounts( void ){ return (_nbAccounts); }

int	Account::getTotalAmount( void ){ return (_totalAmount); }

int	Account::getNbDeposits( void ){ return (_totalNbDeposits); }

int	Account::getNbWithdrawals( void ){ return (_totalNbWithdrawals); }

void	Account::displayAccountsInfos(void)
{
	Account::_displayTimestamp();
	std::cout << "accounts:" << Account::getNbAccounts() << ";total:" << Account::getTotalAmount()
	<< ";deposits:" << Account::getNbDeposits() << ";withdrawals:" << Account::getNbWithdrawals() << "\n";
}

// CONSTRUCTOR
Account::Account(int initial_deposit)
{
	this->_accountIndex = this->_nbAccounts;
	this->_amount = initial_deposit;
	this->_nbDeposits = 0;
	this->_nbWithdrawals = 0;
	this->_totalAmount += initial_deposit;
	this->_nbAccounts++;
	Account::_displayTimestamp();
	std::cout << "index:" << this->_accountIndex << ";amount:" << initial_deposit << ";created\n";
}

// DESTRUCTOR
Account::~Account( void )
{
	Account::_displayTimestamp();
	std::cout << "index:" << this->_accountIndex << ";amount:" << this->_amount
	<< ";closed\n";
	this->_nbAccounts--;
	this->_totalAmount -= this->_amount;
	this->_totalNbDeposits -= this->_nbDeposits;
	this->_totalNbWithdrawals -= this->_nbWithdrawals;
}

// METHODS

void	Account::makeDeposit(int deposit)
{
	Account::_displayTimestamp();
	std::cout << "index:" << this->_accountIndex << ";p_amount:" << this->_amount
	<< ";deposit:" << deposit << ";amount:" << this->_amount + deposit << ";nb_deposits:1\n";
	this->_nbDeposits++;
	this->_amount += deposit;
	Account::_totalNbDeposits++;
	Account::_totalAmount += deposit;
}

bool	Account::makeWithdrawal( int withdrawal )
{
	Account::_displayTimestamp();
	if (withdrawal > this->_amount)
	{
		std::cout << "index:" << this->_accountIndex << ";p_amount:" << this->_amount
		<< ";withdrawal:refused\n";
		return (false);
	}
	else
	{
		std::cout << "index:" << this->_accountIndex << ";p_amount:" << this->_amount
		<< ";withdrawal:" << withdrawal << ";amount:" << this->_amount - withdrawal
		<< ";nb_withdrawals:1\n";
		this->_nbWithdrawals++;
		this->_amount -= withdrawal;
		Account::_totalNbWithdrawals++;
		Account::_totalAmount -= withdrawal;
		return (true);
	}
}

int		Account::checkAmount( void ) const{ return (this->_amount); }

void	Account::displayStatus( void ) const
{
	Account::_displayTimestamp();
	std::cout << "index:" << this->_accountIndex << ";amount:" << this->_amount
	<< ";deposits:" << this->_nbDeposits << ";withdrawals:" << this->_nbWithdrawals << "\n";
}

void	Account::_displayTimestamp( void )
{
	char timestamp[19];
	std::time_t time = std::time(NULL);
	std::strftime(timestamp, 19, "[%Y%m%d_%H%M%S] ", std::localtime(&time));
	std::cout << timestamp;
}
