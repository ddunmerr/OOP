#pragma once
#include "Actor.h"
#include "consts.h"

class CHomer : public CActor
{
public:
	CHomer(Bank& bank, AccountId accountId, AccountId margeAccountId, Money salary);

	Money Act(int step) override; // Возвращает сумму наличных для детей

private:
	AccountId m_margeAccountId;
	Money m_salary;
	Money m_electricityBill;
	Money m_homeAllowance;
};
