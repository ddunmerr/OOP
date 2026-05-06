#include "stdafx.h"
#include "../task3/Bank.h"

BOOST_AUTO_TEST_SUITE(Bank_tests)

	BOOST_AUTO_TEST_CASE(initial_cash_is_set_correctly)
	{
		Bank bank(1000);
		BOOST_CHECK_EQUAL(bank.GetCash(), 1000);
	}

	BOOST_AUTO_TEST_CASE(negative_initial_cash_throws)
	{
		BOOST_CHECK_THROW(Bank(-100), BankOperationError);
	}

	BOOST_AUTO_TEST_CASE(can_open_account)
	{
		Bank bank(1000);
		AccountId id = bank.OpenAccount();
		BOOST_CHECK_EQUAL(bank.GetAccountBalance(id), 0);
	}

	BOOST_AUTO_TEST_CASE(opened_accounts_have_unique_ids)
	{
		Bank bank(1000);
		AccountId id1 = bank.OpenAccount();
		AccountId id2 = bank.OpenAccount();
		BOOST_CHECK_NE(id1, id2);
	}

	BOOST_AUTO_TEST_CASE(can_deposit_money)
	{
		Bank bank(1000);
		AccountId id = bank.OpenAccount();
		bank.DepositMoney(id, 500);
		BOOST_CHECK_EQUAL(bank.GetAccountBalance(id), 500);
		BOOST_CHECK_EQUAL(bank.GetCash(), 500);
	}

	BOOST_AUTO_TEST_CASE(cannot_deposit_more_than_cash)
	{
		Bank bank(100);
		AccountId id = bank.OpenAccount();
		BOOST_CHECK_THROW(bank.DepositMoney(id, 200), BankOperationError);
	}

	BOOST_AUTO_TEST_CASE(cannot_deposit_negative_amount)
	{
		Bank bank(1000);
		AccountId id = bank.OpenAccount();
		BOOST_CHECK_THROW(bank.DepositMoney(id, -100), std::out_of_range);
	}

	BOOST_AUTO_TEST_CASE(cannot_deposit_to_nonexistent_account)
	{
		Bank bank(1000);
		BOOST_CHECK_THROW(bank.DepositMoney(999, 100), BankOperationError);
	}

	BOOST_AUTO_TEST_CASE(can_withdraw_money)
	{
		Bank bank(1000);
		AccountId id = bank.OpenAccount();
		bank.DepositMoney(id, 500);
		bank.WithdrawMoney(id, 200);
		BOOST_CHECK_EQUAL(bank.GetAccountBalance(id), 300);
		BOOST_CHECK_EQUAL(bank.GetCash(), 700);
	}

	BOOST_AUTO_TEST_CASE(cannot_withdraw_more_than_balance)
	{
		Bank bank(1000);
		AccountId id = bank.OpenAccount();
		bank.DepositMoney(id, 100);
		BOOST_CHECK_THROW(bank.WithdrawMoney(id, 200), BankOperationError);
	}

	BOOST_AUTO_TEST_CASE(cannot_withdraw_negative_amount)
	{
		Bank bank(1000);
		AccountId id = bank.OpenAccount();
		BOOST_CHECK_THROW(bank.WithdrawMoney(id, -100), std::out_of_range);
	}

	BOOST_AUTO_TEST_CASE(try_withdraw_returns_false_on_insufficient_funds)
	{
		Bank bank(1000);
		AccountId id = bank.OpenAccount();
		bank.DepositMoney(id, 100);
		BOOST_CHECK(!bank.TryWithdrawMoney(id, 200));
		BOOST_CHECK_EQUAL(bank.GetAccountBalance(id), 100);
		BOOST_CHECK_EQUAL(bank.GetCash(), 900);
	}

	BOOST_AUTO_TEST_CASE(try_withdraw_succeeds_with_sufficient_funds)
	{
		Bank bank(1000);
		AccountId id = bank.OpenAccount();
		bank.DepositMoney(id, 500);
		BOOST_CHECK(bank.TryWithdrawMoney(id, 200));
		BOOST_CHECK_EQUAL(bank.GetAccountBalance(id), 300);
	}

	BOOST_AUTO_TEST_CASE(can_send_money_between_accounts)
	{
		Bank bank(1000);
		AccountId id1 = bank.OpenAccount();
		AccountId id2 = bank.OpenAccount();
		bank.DepositMoney(id1, 500);

		bank.SendMoney(id1, id2, 300);

		BOOST_CHECK_EQUAL(bank.GetAccountBalance(id1), 200);
		BOOST_CHECK_EQUAL(bank.GetAccountBalance(id2), 300);
	}

	BOOST_AUTO_TEST_CASE(send_money_rolls_back_on_error)
	{
		Bank bank(1000);
		AccountId id1 = bank.OpenAccount();
		AccountId id2 = bank.OpenAccount();
		bank.DepositMoney(id1, 500);

		// Симулируем ошибку — несуществующий счёт
		BOOST_CHECK_THROW(bank.SendMoney(id1, 999, 300), BankOperationError);

		// Баланс отправителя не изменился
		BOOST_CHECK_EQUAL(bank.GetAccountBalance(id1), 500);
	}

	BOOST_AUTO_TEST_CASE(cannot_send_more_than_balance)
	{
		Bank bank(1000);
		AccountId id1 = bank.OpenAccount();
		AccountId id2 = bank.OpenAccount();
		bank.DepositMoney(id1, 100);

		BOOST_CHECK_THROW(bank.SendMoney(id1, id2, 200), BankOperationError);
	}

	BOOST_AUTO_TEST_CASE(cannot_send_negative_amount)
	{
		Bank bank(1000);
		AccountId id1 = bank.OpenAccount();
		AccountId id2 = bank.OpenAccount();
		BOOST_CHECK_THROW(bank.SendMoney(id1, id2, -100), std::out_of_range);
	}

	BOOST_AUTO_TEST_CASE(try_send_money_returns_false_on_insufficient_funds)
	{
		Bank bank(1000);
		AccountId id1 = bank.OpenAccount();
		AccountId id2 = bank.OpenAccount();
		bank.DepositMoney(id1, 50);

		BOOST_CHECK(!bank.TrySendMoney(id1, id2, 100));
		BOOST_CHECK_EQUAL(bank.GetAccountBalance(id1), 50);
		BOOST_CHECK_EQUAL(bank.GetAccountBalance(id2), 0);
	}

	BOOST_AUTO_TEST_CASE(can_close_account)
	{
		Bank bank(1000);
		AccountId id = bank.OpenAccount();
		bank.DepositMoney(id, 300);

		Money returned = bank.CloseAccount(id);

		BOOST_CHECK_EQUAL(returned, 300);
		BOOST_CHECK_EQUAL(bank.GetCash(), 1000); // 700 было + 300 вернулось = 1000
	}

	BOOST_AUTO_TEST_CASE(closed_account_throws_on_access)
	{
		Bank bank(1000);
		AccountId id = bank.OpenAccount();
		bank.CloseAccount(id);
		BOOST_CHECK_THROW(bank.GetAccountBalance(id), BankOperationError);
	}

	BOOST_AUTO_TEST_CASE(total_money_is_conserved)
	{
		const Money initialCash = 10000;
		Bank bank(initialCash);

		AccountId id1 = bank.OpenAccount();
		AccountId id2 = bank.OpenAccount();
		AccountId id3 = bank.OpenAccount();

		bank.DepositMoney(id1, 3000);
		bank.DepositMoney(id2, 2000);
		bank.WithdrawMoney(id1, 500);
		bank.SendMoney(id2, id3, 700);

		BOOST_CHECK_EQUAL(bank.GetTotalMoney(), initialCash);
	}

BOOST_AUTO_TEST_SUITE_END()
