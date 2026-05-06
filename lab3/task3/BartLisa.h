#pragma once
#include "Actor.h"
#include "consts.h"

class CBartLisa : public CActor
{
public:
	CBartLisa(Bank& bank);

	Money Act(int step) override; // Возвращает сколько потратили
	void ReceiveAllowance(Money amount);

private:
	Money m_spendingAmount = 10;
};
