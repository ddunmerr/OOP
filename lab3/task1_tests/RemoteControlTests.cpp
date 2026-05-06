#include "stdafx.h"
#include "../Task1/RemoteControl.h"
#include "../Task1/TVSet.h"
#include <boost/optional.hpp>
#include <sstream>

using boost::none;
using boost::optional;

// Зависимости RemoteControl-а вынесены в родительскую структуру,
// чтобы гарантировать их создание до конструирования самого remote-контрола
struct RemoteControlDependencies
{
	CTVSet tv;
	std::stringstream input;
	std::stringstream output;
};

struct RemoteControlFixture : RemoteControlDependencies
{
	CRemoteControl remoteControl;

	RemoteControlFixture()
		: remoteControl(tv, input, output)
	{
	}

	// Вспомогательная функция для проверки работы команды command
	// Она принимает ожидаемый номер канала expectedChannel и expectedOutput
	void VerifyCommandHandling(const std::string& command, const optional<int>& expectedChannel, const std::string& expectedOutput)
	{
		// Предварительно очищаем содержимое выходного потока
		output = std::stringstream();
		input = std::stringstream();
		BOOST_CHECK(input << command);
		BOOST_CHECK(remoteControl.HandleCommand());
		BOOST_CHECK_EQUAL(tv.IsTurnedOn(), expectedChannel.is_initialized());
		BOOST_CHECK_EQUAL(tv.GetChannel(), expectedChannel.get_value_or(0));
		BOOST_CHECK(input.eof());
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);
	}
};

BOOST_FIXTURE_TEST_SUITE(Remote_Control, RemoteControlFixture)

	BOOST_AUTO_TEST_CASE(can_handle_TurnOn_command)
	{
		VerifyCommandHandling("TurnOn", 1, "TV is turned on\n");
	}

	BOOST_AUTO_TEST_CASE(can_turn_off_tv_which_is_on)
	{
		tv.TurnOn();
		VerifyCommandHandling("TurnOff", none, "TV is turned off\n");
	}

	BOOST_AUTO_TEST_CASE(can_print_tv_info)
	{
		VerifyCommandHandling("Info", none, "TV is turned off\n");
		tv.TurnOn();
		tv.SelectChannel(42);
		VerifyCommandHandling("Info", 42, "TV is turned on\nChannel is: 42\n");
	}

	BOOST_AUTO_TEST_CASE(can_select_a_valid_channel_when_tv_which_is_on)
	{
		tv.TurnOn();
		VerifyCommandHandling("SelectChannel 42", 42, "Channel switched to: \n");
	}

	BOOST_AUTO_TEST_CASE(cant_select_channel_when_tv_is_turned_off)
	{
		VerifyCommandHandling("SelectChannel 42", none, "Can't select channel because TV is turned off\n");
		VerifyCommandHandling("SelectChannel 100", none, "Can't select channel because TV is turned off\n");
	}

	BOOST_AUTO_TEST_CASE(cant_select_an_invalid_channel_when_tv_is_on)
	{
		tv.TurnOn();
		tv.SelectChannel(42);
		VerifyCommandHandling("SelectChannel 100", 42, "Invalid channel\n");
		VerifyCommandHandling("SelectChannel 0", 42, "Invalid channel\n");
	}

	BOOST_AUTO_TEST_CASE(handles_unknown_command_by_returning_false)
	{
		input = std::stringstream("BlahBlah\n");
		BOOST_CHECK(!remoteControl.HandleCommand());
		// Проверяем, что вывод пустой (вывод UNKNOWN_COMMAND делает main, не контроллер)
		BOOST_CHECK(output.str().empty());
	}

	BOOST_AUTO_TEST_CASE(turning_on_already_turned_on_tv_keeps_it_on_and_does_not_change_channel)
	{
		tv.TurnOn();
		tv.SelectChannel(42);
		VerifyCommandHandling("TurnOn", 42, "TV is turned on\n");
	}

	BOOST_AUTO_TEST_CASE(turning_off_already_turned_off_tv_keeps_it_off)
	{
		VerifyCommandHandling("TurnOff", none, "TV is turned off\n");
	}

	BOOST_AUTO_TEST_CASE(select_channel_with_non_numeric_argument_returns_false)
	{
		tv.TurnOn();
		input = std::stringstream("SelectChannel abc");
		BOOST_CHECK(!remoteControl.HandleCommand());
	}

	BOOST_AUTO_TEST_CASE(select_channel_without_argument_returns_false)
	{
		tv.TurnOn();
		input = std::stringstream("SelectChannel");
		BOOST_CHECK(!remoteControl.HandleCommand());
	}

	BOOST_AUTO_TEST_CASE(command_with_leading_and_trailing_spaces_is_handled)
	{
		VerifyCommandHandling("  TurnOn  ", 1, "TV is turned on\n");
	}

	BOOST_AUTO_TEST_CASE(empty_input_is_treated_as_unknown_command)
	{
		input = std::stringstream("\n");
		BOOST_CHECK(!remoteControl.HandleCommand());
	}

BOOST_AUTO_TEST_SUITE_END()
