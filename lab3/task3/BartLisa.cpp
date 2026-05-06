#include "BartLisa.h"

CBartLisa::CBartLisa(Bank& bank)
	: CActor(BART_AND_LISA, bank)
{
}

void CBartLisa::ReceiveAllowance(Money amount)
{
	ReceiveCash(amount);
	Log(RECEIVED_ALLOWANCE + std::to_string(amount));
}

Money CBartLisa::Act(int step)
{
	if (SpendCash(m_spendingAmount))
	{
		Log(SPENT_CASH_AT_APU + std::to_string(m_spendingAmount));
		return m_spendingAmount;
	}
	else
	{
		Log(NO_CASH_TO_SPEND);
		return 0;
	}
}
