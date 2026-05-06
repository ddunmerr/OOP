#pragma once
#include "Bank.h"
#include "consts.h"
#include <iostream>
#include <string>

class CActor
{
public:
	CActor(const std::string& name, Bank& bank);
	CActor(const std::string& name, Bank& bank, AccountId accountId);
	virtual ~CActor() = default;

	virtual Money Act(int step) = 0;

	[[nodiscard]] std::string GetName() const;
	[[nodiscard]] AccountId GetAccountId() const;
	[[nodiscard]] bool HasAccount() const;
	[[nodiscard]] Money GetCash() const;
	[[nodiscard]] Money GetAccountBalance() const;

	void Log(const std::string& message) const;

protected:
	void ReceiveCash(Money amount);
	bool SpendCash(Money amount);

	std::string m_name;
	Bank& m_bank;
	AccountId m_accountId;
	Money m_cash = 0;
};
