#pragma once
#include "consts.h"
#include <map>
#include <stdexcept>
#include <string>

using AccountId = unsigned long long;
using Money = long long;

class BankOperationError : public std::runtime_error
{
public:
	using runtime_error::runtime_error;
};

class Bank
{
public:
	explicit Bank(Money cash);

	Bank(const Bank&) = delete;
	Bank& operator=(const Bank&) = delete;

	void SendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount);
	[[nodiscard]] bool TrySendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount);

	[[nodiscard]] Money GetCash() const;

	Money GetAccountBalance(AccountId accountId) const;

	void WithdrawMoney(AccountId account, Money amount);
	[[nodiscard]] bool TryWithdrawMoney(AccountId account, Money amount);

	void DepositMoney(AccountId account, Money amount);

	[[nodiscard]] AccountId OpenAccount();

	[[nodiscard]] Money CloseAccount(AccountId accountId);

	// Для тестирования
	[[nodiscard]] Money GetTotalMoney() const;

private:
	void ValidateAccountExists(AccountId accountId) const;
	void ValidateNotNegative(Money amount, const std::string& paramName) const;

	Money m_cash;
	std::map<AccountId, Money> m_accounts;
	AccountId m_nextAccountId = 1;
};
