#include "Bank.h"
#include <stdexcept>
Bank::Bank(Money cash)
	: m_cash(cash)
{
	if (cash < 0)
	{
		throw BankOperationError(ERROR_INITIAL_CASH_CANT_BE_NEGATIVE);
	}
}

void Bank::ValidateAccountExists(AccountId accountId) const
{
	if (m_accounts.find(accountId) == m_accounts.end())
	{
		throw BankOperationError(ERROR_ACCOUNT_DOESNT_EXIST + std::to_string(accountId));
	}
}

void Bank::ValidateNotNegative(Money amount, const std::string& paramName) const
{
	if (amount < 0)
	{
		throw std::out_of_range(paramName + ERROR_CANT_BE_NEGATIVE);
	}
}

void Bank::SendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount)
{
	ValidateNotNegative(amount, AMOUNT);
	ValidateAccountExists(srcAccountId);
	ValidateAccountExists(dstAccountId);

	if (m_accounts[srcAccountId] < amount)
	{
		throw BankOperationError(ERROR_INSUFFICIENT_FUNDS_ON_ACCOUNT + std::to_string(srcAccountId));
	}

	m_accounts[srcAccountId] -= amount;

	try
	{
		m_accounts[dstAccountId] += amount;
	}
	catch (...)
	{
		m_accounts[srcAccountId] += amount;
		throw;
	}
}

bool Bank::TrySendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount)
{
	ValidateNotNegative(amount, AMOUNT);
	ValidateAccountExists(srcAccountId);
	ValidateAccountExists(dstAccountId);

	if (m_accounts[srcAccountId] < amount)
	{
		return false;
	}

	m_accounts[srcAccountId] -= amount;
	m_accounts[dstAccountId] += amount;
	return true;
}

Money Bank::GetCash() const
{
	return m_cash;
}

Money Bank::GetAccountBalance(AccountId accountId) const
{
	ValidateAccountExists(accountId);
	return m_accounts.at(accountId);
}

void Bank::WithdrawMoney(AccountId account, Money amount)
{
	ValidateNotNegative(amount, AMOUNT);
	ValidateAccountExists(account);

	if (m_accounts[account] < amount)
	{
		throw BankOperationError(ERROR_INSUFFICIENT_FUNDS_ON_ACCOUNT + std::to_string(account));
	}

	m_accounts[account] -= amount;
	m_cash += amount;
}

bool Bank::TryWithdrawMoney(AccountId account, Money amount)
{
	ValidateNotNegative(amount, AMOUNT);
	ValidateAccountExists(account);

	if (m_accounts[account] < amount)
	{
		return false;
	}

	m_accounts[account] -= amount;
	m_cash += amount;
	return true;
}

void Bank::DepositMoney(AccountId account, Money amount)
{
	ValidateNotNegative(amount, AMOUNT);
	ValidateAccountExists(account);

	if (m_cash < amount)
	{
		throw BankOperationError(ERROR_NOT_ENOUGH_CASH_ON_CIRCULATION);
	}

	m_accounts[account] += amount;
	m_cash -= amount;
}

AccountId Bank::OpenAccount()
{
	AccountId newId = m_nextAccountId++;
	m_accounts[newId] = 0;
	return newId;
}

Money Bank::CloseAccount(AccountId accountId)
{
	ValidateAccountExists(accountId);

	Money balance = m_accounts[accountId];
	m_cash += balance;
	m_accounts.erase(accountId);

	return balance;
}

Money Bank::GetTotalMoney() const
{
	Money total = m_cash;
	for (const auto& [id, balance] : m_accounts)
	{
		total += balance;
	}
	return total;
}
