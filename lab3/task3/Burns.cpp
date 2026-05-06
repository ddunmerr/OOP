#include "Burns.h"

CBurns::CBurns(Bank& bank, AccountId accountId, AccountId homerAccountId, Money homerSalary)
	: CActor(BURNS, bank, accountId)
	, m_homerAccountId(homerAccountId)
	, m_homerSalary(homerSalary)
{
}

Money CBurns::Act(int step)
{
	if (m_bank.TrySendMoney(m_accountId, m_homerAccountId, m_homerSalary))
	{
		Log(PAID_SALARY + std::to_string(m_homerSalary));
		return m_homerSalary;
	}
	else
	{
		Log(COULDNT_PAY_HOMER);
		return 0;
	}
}
