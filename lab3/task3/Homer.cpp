#include "Homer.h"

CHomer::CHomer(Bank& bank, AccountId accountId, AccountId margeAccountId, Money salary)
	: CActor(HOMER, bank, accountId)
	, m_margeAccountId(margeAccountId)
	, m_salary(salary)
	, m_electricityBill(salary / 4)
	, m_homeAllowance(salary / 3)
{
}

Money CHomer::Act(int step)
{
	Money kidsCash = 0;

	// Переводим деньги Мардж
	if (m_bank.TrySendMoney(m_accountId, m_margeAccountId, m_homeAllowance))
	{
		Log(SENT_MONEY_TO_MARGE + std::to_string(m_homeAllowance));
	}
	else
	{
		Log(COULDNT_SEND_MONEY_TO_MARGE);
	}

	// Снимаем на электричество (наличные)
	if (m_bank.TryWithdrawMoney(m_accountId, m_electricityBill))
	{
		ReceiveCash(m_electricityBill);
		Log(WITHDREW_FOR_ELECTRICITY + std::to_string(m_electricityBill));
	}

	// Снимаем наличные для детей
	kidsCash = m_salary / 10;
	if (m_bank.TryWithdrawMoney(m_accountId, kidsCash))
	{
		Log(WITHDREW_FOR_KIDS + std::to_string(kidsCash));
	}
	else
	{
		kidsCash = 0;
	}

	return kidsCash;
}
