#include "stdafx.h"
#include "../task3/Bank.h"
#include "../task3/Marge.h"

struct MargeFixture
{
	Bank bank{ 50000 };
	AccountId margeId;
	AccountId apuId;

	MargeFixture()
	{
		margeId = bank.OpenAccount();
		apuId = bank.OpenAccount();
		bank.DepositMoney(margeId, 1000);
	}
};

BOOST_FIXTURE_TEST_SUITE(Marge, MargeFixture)

	BOOST_AUTO_TEST_CASE(has_valid_account)
	{
		CMarge marge(bank, margeId, apuId);
		BOOST_CHECK(marge.HasAccount());
	}

	BOOST_AUTO_TEST_CASE(buys_groceries_from_apu)
	{
		CMarge marge(bank, margeId, apuId);
		Money beforeApuBalance = bank.GetAccountBalance(apuId);

		marge.Act(1);

		Money afterApuBalance = bank.GetAccountBalance(apuId);
		BOOST_CHECK(afterApuBalance > beforeApuBalance);
	}

	BOOST_AUTO_TEST_CASE(cannot_buy_when_insufficient_funds)
	{
		// Снимаем почти все деньги
		bank.WithdrawMoney(margeId, 900);

		CMarge marge(bank, margeId, apuId);
		Money beforeApuBalance = bank.GetAccountBalance(apuId);

		marge.Act(1);

		// Баланс Апу не изменился
		BOOST_CHECK_EQUAL(bank.GetAccountBalance(apuId), beforeApuBalance);
	}

BOOST_AUTO_TEST_SUITE_END()
