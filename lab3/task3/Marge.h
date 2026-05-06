#pragma once
#include "Actor.h"
#include "consts.h"

class CMarge : public CActor
{
public:
	CMarge(Bank& bank, AccountId accountId, AccountId apuAccountId);

	Money Act(int step) override;

private:
	AccountId m_apuAccountId;
	Money m_groceryBudget = 200;
};
