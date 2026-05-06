#pragma once
#include "Actor.h"
#include "consts.h"

class CBurns : public CActor
{
public:
	CBurns(Bank& bank, AccountId accountId, AccountId homerAccountId, Money homerSalary);

	Money Act(int step) override;

private:
	AccountId m_homerAccountId;
	Money m_homerSalary;
};
