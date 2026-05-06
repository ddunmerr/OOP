#include "stdafx.h"
#include "../task3/Actor.h"
#include "../task3/Bank.h"

// Конкретный актор для тестирования базового класса
class CTestActor : public CActor
{
public:
	CTestActor(const std::string& name, Bank& bank, AccountId accountId)
		: CActor(name, bank, accountId)
	{
	}

	CTestActor(const std::string& name, Bank& bank)
		: CActor(name, bank)
	{
	}

	Money Act(int step) override
	{
		return 0; // Ничего не делаем
	}

	// Публичные обёртки для тестирования protected методов
	void TestReceiveCash(Money amount)
	{
		ReceiveCash(amount);
	}

	bool TestSpendCash(Money amount)
	{
		return SpendCash(amount);
	}
};

// Тестируем актора с банковским счётом
struct ActorWithAccountFixture
{
	Bank bank{ 10000 };
	AccountId accountId;

	ActorWithAccountFixture()
	{
		accountId = bank.OpenAccount();
		bank.DepositMoney(accountId, 1000);
	}
};

BOOST_FIXTURE_TEST_SUITE(Actor_with_account, ActorWithAccountFixture)

	BOOST_AUTO_TEST_CASE(has_valid_account_id)
	{
		CTestActor actor("Test", bank, accountId);
		BOOST_CHECK(actor.HasAccount());
		BOOST_CHECK_EQUAL(actor.GetAccountId(), accountId);
	}

	BOOST_AUTO_TEST_CASE(initial_cash_is_zero)
	{
		CTestActor actor("Test", bank, accountId);
		BOOST_CHECK_EQUAL(actor.GetCash(), 0);
	}

	BOOST_AUTO_TEST_CASE(can_receive_cash)
	{
		CTestActor actor("Test", bank, accountId);
		actor.TestReceiveCash(500);
		BOOST_CHECK_EQUAL(actor.GetCash(), 500);
	}

	BOOST_AUTO_TEST_CASE(can_spend_cash)
	{
		CTestActor actor("Test", bank, accountId);
		actor.TestReceiveCash(500);
		bool result = actor.TestSpendCash(200);
		BOOST_CHECK(result);
		BOOST_CHECK_EQUAL(actor.GetCash(), 300);
	}

	BOOST_AUTO_TEST_CASE(cannot_spend_more_than_available)
	{
		CTestActor actor("Test", bank, accountId);
		actor.TestReceiveCash(100);
		bool result = actor.TestSpendCash(200);
		BOOST_CHECK(!result);
		BOOST_CHECK_EQUAL(actor.GetCash(), 100);
	}

	BOOST_AUTO_TEST_CASE(account_balance_is_correct)
	{
		CTestActor actor("Test", bank, accountId);
		BOOST_CHECK_EQUAL(actor.GetAccountBalance(), 1000);
	}

BOOST_AUTO_TEST_SUITE_END()

// Тестируем актора без счёта
struct ActorWithoutAccountFixture
{
	Bank bank{ 10000 };
};

BOOST_FIXTURE_TEST_SUITE(Actor_without_account, ActorWithoutAccountFixture)

	BOOST_AUTO_TEST_CASE(has_no_account)
	{
		CTestActor actor("Test", bank);
		BOOST_CHECK(!actor.HasAccount());
		BOOST_CHECK_EQUAL(actor.GetAccountId(), 0);
	}

	BOOST_AUTO_TEST_CASE(account_balance_returns_zero)
	{
		CTestActor actor("Test", bank);
		BOOST_CHECK_EQUAL(actor.GetAccountBalance(), 0);
	}

	BOOST_AUTO_TEST_CASE(can_only_use_cash)
	{
		CTestActor actor("Test", bank);
		actor.TestReceiveCash(300);
		BOOST_CHECK_EQUAL(actor.GetCash(), 300);
		BOOST_CHECK_EQUAL(actor.GetAccountBalance(), 0);
	}

BOOST_AUTO_TEST_SUITE_END()
