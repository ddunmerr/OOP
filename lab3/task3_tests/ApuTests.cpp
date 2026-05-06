#include "stdafx.h"
#include "../task3/Apu.h"
#include "../task3/Bank.h"

struct ApuFixture
{
	Bank bank{ 50000 };
	AccountId apuId;
	AccountId burnsId;

	ApuFixture()
	{
		apuId = bank.OpenAccount();
		burnsId = bank.OpenAccount();
		bank.DepositMoney(apuId, 2000);
	}
};

BOOST_FIXTURE_TEST_SUITE(Apu, ApuFixture)

	BOOST_AUTO_TEST_CASE(has_valid_account)
	{
		CApu apu(bank, apuId, burnsId);
		BOOST_CHECK(apu.HasAccount());
	}

	BOOST_AUTO_TEST_CASE(pays_electricity_to_burns)
	{
		CApu apu(bank, apuId, burnsId);
		Money beforeBurnsBalance = bank.GetAccountBalance(burnsId);

		apu.Act(1);

		Money afterBurnsBalance = bank.GetAccountBalance(burnsId);
		BOOST_CHECK(afterBurnsBalance > beforeBurnsBalance);
	}

	BOOST_AUTO_TEST_CASE(can_receive_cash_from_customers)
	{
		CApu apu(bank, apuId, burnsId);
		apu.ReceiveCashFromCustomer(500);
		BOOST_CHECK_EQUAL(apu.GetCash(), 500);
	}

	BOOST_AUTO_TEST_CASE(deposits_all_cash_to_account)
	{
		CApu apu(bank, apuId, burnsId);
		apu.ReceiveCashFromCustomer(500);

		apu.Act(1);

		BOOST_CHECK_EQUAL(apu.GetCash(), 0);
		BOOST_CHECK(bank.GetAccountBalance(apuId) >= 2000 + 500 - 150); // +500 нал, -150 электричество
	}

	BOOST_AUTO_TEST_CASE(does_nothing_when_no_cash)
	{
		CApu apu(bank, apuId, burnsId);
		Money beforeBalance = bank.GetAccountBalance(apuId);

		apu.Act(1);

		// Только оплата электричества
		BOOST_CHECK(bank.GetAccountBalance(apuId) <= beforeBalance);
	}

BOOST_AUTO_TEST_SUITE_END()
