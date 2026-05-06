#include "Marge.h"

CMarge::CMarge(Bank& bank, AccountId accountId, AccountId apuAccountId)
	: CActor(MARGE, bank, accountId)
	, m_apuAccountId(apuAccountId)
{
}

Money CMarge::Act(int step)
{
	if (m_bank.TrySendMoney(m_accountId, m_apuAccountId, m_groceryBudget))
	{
		Log(BOUGHT_GROCERIES + std::to_string(m_groceryBudget));
		return m_groceryBudget;
	}
	else
	{
		Log(COULDNT_BUY_GROCERIES);
		return 0;
	}
}
