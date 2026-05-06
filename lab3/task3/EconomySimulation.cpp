#include "EconomySimulation.h"
#include <iostream>

CEconomySimulation::CEconomySimulation(Money initialCash, int iterations)
	: m_bank(initialCash)
	, m_iterations(iterations)
	, m_initialTotalMoney(initialCash)
{
	Initialize();
}

void CEconomySimulation::Initialize()
{
	const Money salary = 500;
	const Money initialDeposit = 2000;

	// Открываем счета
	AccountId homerId = m_bank.OpenAccount();
	AccountId margeId = m_bank.OpenAccount();
	AccountId apuId = m_bank.OpenAccount();
	AccountId burnsId = m_bank.OpenAccount();

	// Кладём начальные деньги на счета
	// ВАЖНО: сумма депозитов НЕ может превышать m_cash банка
	m_bank.DepositMoney(burnsId, 4000);
	m_bank.DepositMoney(homerId, 2000);
	m_bank.DepositMoney(apuId, 1000);
	m_bank.DepositMoney(margeId, 500);

	// Создаём акторов
	m_burns = std::make_unique<CBurns>(m_bank, burnsId, homerId, salary);
	m_apu = std::make_unique<CApu>(m_bank, apuId, burnsId);
	m_marge = std::make_unique<CMarge>(m_bank, margeId, apuId);
	m_homer = std::make_unique<CHomer>(m_bank, homerId, margeId, salary);
	m_bartLisa = std::make_unique<CBartLisa>(m_bank);
}

void CEconomySimulation::Step(int step)
{
	std::cout << STEP_BEGIN << step << STEP_END << std::endl;

	// 1. Бернс платит зарплату Гомеру
	m_burns->Act(step);

	// 2. Гомер: переводит Мардж, платит электричество, снимает наличные детям
	Money kidsCash = m_homer->Act(step);
	if (kidsCash > 0)
	{
		m_bartLisa->ReceiveAllowance(kidsCash);
	}

	// 3. Мардж покупает продукты у Апу
	m_marge->Act(step);

	// 4. Апу: получает наличные от детей, платит электричество, депонирует наличные
	// Дети уже потратили деньги у Апу
	m_apu->Act(step);

	// 5. Дети тратят наличные у Апу (логика обрабатывается внутри)
	Money spentByKids = m_bartLisa->Act(step);
	if (spentByKids > 0)
	{
		m_apu->ReceiveCashFromCustomer(spentByKids);
	}
}

void CEconomySimulation::PrintFinalReport() const
{
	std::cout << FINAL_REPORT << std::endl;

	auto printActorWithAccount = [](const CActor& actor) {
		std::cout << actor.GetName() << ": "
				  << ACCOUNT << actor.GetAccountBalance()
				  << CASH << actor.GetCash()
				  << std::endl;
	};

	auto printActorWithoutAccount = [](const CActor& actor) {
		std::cout << actor.GetName() << ": "
				  << CASH << actor.GetCash() << NO_BANK_ACCOUNT
				  << std::endl;
	};

	printActorWithAccount(*m_homer);
	printActorWithAccount(*m_marge);
	printActorWithoutAccount(*m_bartLisa);
	printActorWithAccount(*m_apu);
	printActorWithAccount(*m_burns);

	// Банковские деньги
	Money bankCash = m_bank.GetCash();

	// Деньги на счетах
	Money totalOnAccounts = m_homer->GetAccountBalance() + m_marge->GetAccountBalance() + m_apu->GetAccountBalance() + m_burns->GetAccountBalance();

	// Наличные у акторов
	Money totalCashInActors = m_homer->GetCash() + m_marge->GetCash() + m_bartLisa->GetCash() + m_apu->GetCash() + m_burns->GetCash();

	// Общая сумма = банковская наличность + счета + наличные акторов
	// На самом деле: банковская наличность УЖЕ включает наличные, которые В БАНКЕ
	// А наличные у акторов = это деньги, снятые со счетов или полученные иначе
	// Итог: bankCash + totalOnAccounts ДОЛЖНО равняться initialTotalMoney
	// А cash у акторов — это деньги, которые УЖЕ учтены в bankCash (как изъятые из оборота)

	Money systemTotal = bankCash + totalOnAccounts;

	std::cout << CASH_IN_CIRCULATION << bankCash << std::endl;
	std::cout << TOTAL_ON_ACCOUNTS << totalOnAccounts << std::endl;
	std::cout << TOTAL_CASH_HELD_BY_ACTORS << totalCashInActors << std::endl;
	std::cout << SYSTEM_TOTAL << systemTotal << std::endl;
	std::cout << EXPECTED_TOTAL << m_initialTotalMoney << std::endl;

	// Проверка: bankCash + сумма на счетах == initialTotalMoney
	if (systemTotal == m_initialTotalMoney)
	{
		std::cout << SYSTEM_IS_CONSISTENT << std::endl;
	}
	else
	{
		std::cout << SYSTEM_INCONSISTENT << m_initialTotalMoney
				  << SYSTEM_GOT << systemTotal << DIFFERENCE
				  << m_initialTotalMoney - systemTotal << std::endl;
	}

	// Дополнительная проверка: сумма наличных у акторов не превышает bankCash
	if (totalCashInActors <= bankCash + totalOnAccounts)
	{
		std::cout << ACTORS_HOLD_IN_CASH << totalCashInActors << std::endl;
	}
}

void CEconomySimulation::Run()
{
	for (int i = 1; i <= m_iterations; ++i)
	{
		Step(i);
	}
	PrintFinalReport();
}
