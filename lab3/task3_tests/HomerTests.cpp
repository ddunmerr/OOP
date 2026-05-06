#include "stdafx.h"
#include "../task3/Bank.h"
#include "../task3/Homer.h"

struct HomerFixture
{
	Bank bank{ 50000 };
	AccountId homerId;
	AccountId margeId;

	HomerFixture()
	{
		homerId = bank.OpenAccount();
		margeId = bank.OpenAccount();
		bank.DepositMoney(homerId, 2000);
	}
};

BOOST_FIXTURE_TEST_SUITE(Homer, HomerFixture)

	BOOST_AUTO_TEST_CASE(has_valid_account)
	{
		CHomer homer(bank, homerId, margeId, 500);
		BOOST_CHECK(homer.HasAccount());
		BOOST_CHECK_EQUAL(homer.GetAccountId(), homerId);
	}

	BOOST_AUTO_TEST_CASE(sends_home_allowance_to_marge)
	{
		CHomer homer(bank, homerId, margeId, 500);
		Money kidsCash = homer.Act(1);

		// Мардж получила деньги (1/3 от зарплаты = 166)
		Money margeBalance = bank.GetAccountBalance(margeId);
		BOOST_CHECK(margeBalance > 0);
	}

	BOOST_AUTO_TEST_CASE(withdraws_cash_for_children)
	{
		CHomer homer(bank, homerId, margeId, 500);
		Money kidsCash = homer.Act(1);

		// Дети получают 1/10 от зарплаты = 50
		BOOST_CHECK_EQUAL(kidsCash, 50);
	}

	BOOST_AUTO_TEST_CASE(withdraws_cash_for_electricity)
	{
		CHomer homer(bank, homerId, margeId, 500);
		Money beforeCash = homer.GetCash();
		homer.Act(1);

		// Гомер получил наличные на электричество (1/4 от зарплаты = 125)
		BOOST_CHECK_EQUAL(homer.GetCash(), 125);
	}

	BOOST_AUTO_TEST_CASE(returns_zero_when_insufficient_funds)
	{
		// Снимаем все деньги со счёта Гомера
		bank.WithdrawMoney(homerId, 2000);

		CHomer homer(bank, homerId, margeId, 500);
		Money kidsCash = homer.Act(1);

		BOOST_CHECK_EQUAL(kidsCash, 0);
	}

BOOST_AUTO_TEST_SUITE_END()
