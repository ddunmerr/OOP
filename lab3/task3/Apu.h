#pragma once
#include "Actor.h"
#include "consts.h"

class CApu : public CActor
{
public:
	CApu(Bank& bank, AccountId accountId, AccountId burnsAccountId);

	Money Act(int step) override;
	void ReceiveCashFromCustomer(Money amount);

private:
	AccountId m_burnsAccountId;
	Money m_electricityPayment = 150;
};
