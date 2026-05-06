#include "stdafx.h"
#include "../task3/Bank.h"
#include "../task3/BartLisa.h"

struct BartLisaFixture
{
	Bank bank{ 50000 };
};

BOOST_FIXTURE_TEST_SUITE(Bart_and_Lisa, BartLisaFixture)

	BOOST_AUTO_TEST_CASE(has_no_bank_account)
	{
		CBartLisa bartLisa(bank);
		BOOST_CHECK(!bartLisa.HasAccount());
		BOOST_CHECK_EQUAL(bartLisa.GetAccountId(), 0);
	}

	BOOST_AUTO_TEST_CASE(initial_cash_is_zero)
	{
		CBartLisa bartLisa(bank);
		BOOST_CHECK_EQUAL(bartLisa.GetCash(), 0);
	}

	BOOST_AUTO_TEST_CASE(can_receive_allowance)
	{
		CBartLisa bartLisa(bank);
		bartLisa.ReceiveAllowance(100);
		BOOST_CHECK_EQUAL(bartLisa.GetCash(), 100);
	}

	BOOST_AUTO_TEST_CASE(spends_cash_when_available)
	{
		CBartLisa bartLisa(bank);
		bartLisa.ReceiveAllowance(100);

		Money spent = bartLisa.Act(1);

		BOOST_CHECK_EQUAL(spent, 10);
		BOOST_CHECK_EQUAL(bartLisa.GetCash(), 90);
	}

	BOOST_AUTO_TEST_CASE(spends_nothing_when_no_cash)
	{
		CBartLisa bartLisa(bank);

		Money spent = bartLisa.Act(1);

		BOOST_CHECK_EQUAL(spent, 0);
		BOOST_CHECK_EQUAL(bartLisa.GetCash(), 0);
	}

	BOOST_AUTO_TEST_CASE(can_spend_multiple_times_until_broke)
	{
		CBartLisa bartLisa(bank);
		bartLisa.ReceiveAllowance(25);

		// Шаг 1: потратили 10, осталось 15
		Money spent1 = bartLisa.Act(1);
		BOOST_CHECK_EQUAL(spent1, 10);
		BOOST_CHECK_EQUAL(bartLisa.GetCash(), 15);

		// Шаг 2: потратили 10, осталось 5
		Money spent2 = bartLisa.Act(2);
		BOOST_CHECK_EQUAL(spent2, 10);
		BOOST_CHECK_EQUAL(bartLisa.GetCash(), 5);

		// Шаг 3: не могут потратить 10 (всего 5)
		Money spent3 = bartLisa.Act(3);
		BOOST_CHECK_EQUAL(spent3, 0);
		BOOST_CHECK_EQUAL(bartLisa.GetCash(), 5);
	}

BOOST_AUTO_TEST_SUITE_END()
