#include "Actor.h"

CActor::CActor(const std::string& name, Bank& bank)
	: m_name(name)
	, m_bank(bank)
	, m_accountId(0)
{
}

CActor::CActor(const std::string& name, Bank& bank, AccountId accountId)
	: m_name(name)
	, m_bank(bank)
	, m_accountId(accountId)
{
}

std::string CActor::GetName() const
{
	return m_name;
}

AccountId CActor::GetAccountId() const
{
	return m_accountId;
}

bool CActor::HasAccount() const
{
	return m_accountId != 0;
}

Money CActor::GetCash() const
{
	return m_cash;
}

Money CActor::GetAccountBalance() const
{
	if (HasAccount())
	{
		return m_bank.GetAccountBalance(m_accountId);
	}
	return 0;
}

void CActor::Log(const std::string& message) const
{
	std::cout << "[" << m_name << "] " << message << std::endl;
}

void CActor::ReceiveCash(Money amount)
{
	m_cash += amount;
}

bool CActor::SpendCash(Money amount)
{
	if (m_cash < amount)
		return false;
	m_cash -= amount;
	return true;
}
