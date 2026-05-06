#pragma once
#include "Apu.h"
#include "Bank.h"
#include "BartLisa.h"
#include "Burns.h"
#include "Homer.h"
#include "Marge.h"
#include "consts.h"
#include <memory>

class CEconomySimulation
{
public:
	CEconomySimulation(Money initialCash, int iterations);
	void Run();

private:
	void Initialize();
	void Step(int step);
	void PrintFinalReport() const;

	Bank m_bank;
	int m_iterations;
	Money m_initialTotalMoney; // Фиксированная сумма, которую заложили изначально

	std::unique_ptr<CHomer> m_homer;
	std::unique_ptr<CMarge> m_marge;
	std::unique_ptr<CBartLisa> m_bartLisa;
	std::unique_ptr<CApu> m_apu;
	std::unique_ptr<CBurns> m_burns;
};
