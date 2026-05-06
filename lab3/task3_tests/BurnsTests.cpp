#include "stdafx.h"
#include "../task3/Bank.h"
#include "../task3/Burns.h"

struct BurnsFixture
{
	Bank bank{ 50000 };
	AccountId burnsId;
	AccountId homerId;

	BurnsFixture()
	{
		burnsId = bank.OpenAccount();
		homerId = bank.OpenAccount();
		bank.DepositMoney(burnsId, 5000);
	}
};

BOOST_FIXTURE_TEST_SUITE(Mr_Burns, BurnsFixture)

	BOOST_AUTO_TEST_CASE(has_valid_account)
	{
		CBurns burns(bank, burnsId, homerId, 500);
		BOOST_CHECK(burns.HasAccount());
	}

	BOOST_AUTO_TEST_CASE(pays_salary_to_homer)
	{
		CBurns burns(bank, burnsId, homerId, 500);
		Money beforeHomerBalance = bank.GetAccountBalance(homerId);

		Money paid = burns.Act(1);

		BOOST_CHECK_EQUAL(paid, 500);
		Money afterHomerBalance = bank.GetAccountBalance(homerId);
		BOOST_CHECK_EQUAL(afterHomerBalance - beforeHomerBalance, 500);
	}

	BOOST_AUTO_TEST_CASE(cannot_pay_when_insufficient_funds)
	{
		bank.WithdrawMoney(burnsId, 5000);

		CBurns burns(bank, burnsId, homerId, 500);
		Money paid = burns.Act(1);

		BOOST_CHECK_EQUAL(paid, 0);
		BOOST_CHECK_EQUAL(bank.GetAccountBalance(homerId), 0);
	}

	BOOST_AUTO_TEST_CASE(account_decreases_after_paying_salary)
	{
		CBurns burns(bank, burnsId, homerId, 500);
		Money beforeBalance = bank.GetAccountBalance(burnsId);

		burns.Act(1);

		Money afterBalance = bank.GetAccountBalance(burnsId);
		BOOST_CHECK_EQUAL(afterBalance, beforeBalance - 500);
	}

BOOST_AUTO_TEST_SUITE_END()
