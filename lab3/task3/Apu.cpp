#include "Apu.h"

CApu::CApu(Bank& bank, AccountId accountId, AccountId burnsAccountId)
	: CActor(APU, bank, accountId)
	, m_burnsAccountId(burnsAccountId)
{
}

void CApu::ReceiveCashFromCustomer(Money amount)
{
	ReceiveCash(amount);
}

Money CApu::Act(int step)
{
	// Депонируем все наличные на счёт
	if (m_cash > 0)
	{
		try
		{
			m_bank.DepositMoney(m_accountId, m_cash);
			Log(DEPOSITED_CASH + std::to_string(m_cash));
			m_cash = 0;
		}
		catch (const BankOperationError&)
		{
			Log(ERROR_CANT_DEPOSIT);
		}
	}

	// Платим за электричество Бернсу
	if (m_bank.TrySendMoney(m_accountId, m_burnsAccountId, m_electricityPayment))
	{
		Log(PAID_ELECTRICITY + std::to_string(m_electricityPayment));
	}
	else
	{
		Log(COULDNT_PAY_ELECTRICITY);
	}

	return 0;
}
