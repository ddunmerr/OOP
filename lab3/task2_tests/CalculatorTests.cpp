#include "stdafx.h"
#include "../task2/Calculator.h"

BOOST_AUTO_TEST_SUITE(Calculator)

	BOOST_AUTO_TEST_CASE(initially_has_no_identifiers)
	{
		CCalculator calc;
		BOOST_CHECK(!calc.HasIdentifier("x"));
	}

	BOOST_AUTO_TEST_CASE(can_declare_variable)
	{
		CCalculator calc;
		BOOST_CHECK(calc.DeclareVariable("x"));
		BOOST_CHECK(calc.HasIdentifier("x"));
		BOOST_CHECK(calc.IsVariable("x"));
	}

	BOOST_AUTO_TEST_CASE(newly_declared_variable_is_undefined)
	{
		CCalculator calc;
		calc.DeclareVariable("x");
		auto value = calc.GetValue("x");
		BOOST_CHECK(!value.has_value());
	}

	BOOST_AUTO_TEST_CASE(cannot_declare_duplicate_variable)
	{
		CCalculator calc;
		calc.DeclareVariable("x");
		BOOST_CHECK(!calc.DeclareVariable("x"));
	}

	BOOST_AUTO_TEST_CASE(can_set_variable_value_to_number)
	{
		CCalculator calc;
		BOOST_CHECK(calc.SetVariableValue("x", 42.0));
		auto value = calc.GetValue("x");
		BOOST_REQUIRE(value.has_value());
		BOOST_CHECK_EQUAL(*value, 42.0);
	}

	BOOST_AUTO_TEST_CASE(setting_value_to_undeclared_variable_declares_it)
	{
		CCalculator calc;
		BOOST_CHECK(calc.SetVariableValue("x", 42.0));
		BOOST_CHECK(calc.HasIdentifier("x"));
		BOOST_CHECK(calc.IsVariable("x"));
	}

	BOOST_AUTO_TEST_CASE(can_set_variable_value_from_another_variable)
	{
		CCalculator calc;
		calc.SetVariableValue("x", 10.0);
		BOOST_CHECK(calc.SetVariableValue("y", "x"));
		auto value = calc.GetValue("y");
		BOOST_REQUIRE(value.has_value());
		BOOST_CHECK_EQUAL(*value, 10.0);
	}

	BOOST_AUTO_TEST_CASE(setting_value_from_undefined_variable_makes_undefined)
	{
		CCalculator calc;
		calc.DeclareVariable("x");
		calc.SetVariableValue("y", "x");
		auto value = calc.GetValue("y");
		BOOST_CHECK(!value.has_value());
	}

	BOOST_AUTO_TEST_CASE(can_declare_simple_function)
	{
		CCalculator calc;
		calc.SetVariableValue("x", 42.0);
		BOOST_CHECK(calc.DeclareFunction("f", "x"));
		auto value = calc.GetValue("f");
		BOOST_REQUIRE(value.has_value());
		BOOST_CHECK_EQUAL(*value, 42.0);
	}

	BOOST_AUTO_TEST_CASE(function_with_undefined_operand_is_undefined)
	{
		CCalculator calc;
		calc.DeclareVariable("x");
		calc.DeclareFunction("f", "x");
		auto value = calc.GetValue("f");
		BOOST_CHECK(!value.has_value());
	}

	BOOST_AUTO_TEST_CASE(can_declare_binary_function_addition)
	{
		CCalculator calc;
		calc.SetVariableValue("x", 10.0);
		calc.SetVariableValue("y", 20.0);
		calc.DeclareFunction("sum", "x", Operation::Add, "y");
		auto value = calc.GetValue("sum");
		BOOST_REQUIRE(value.has_value());
		BOOST_CHECK_EQUAL(*value, 30.0);
	}

	BOOST_AUTO_TEST_CASE(binary_function_with_undefined_operand_is_undefined)
	{
		CCalculator calc;
		calc.SetVariableValue("x", 10.0);
		calc.DeclareVariable("y");
		calc.DeclareFunction("sum", "x", Operation::Add, "y");
		auto value = calc.GetValue("sum");
		BOOST_CHECK(!value.has_value());
	}

	BOOST_AUTO_TEST_CASE(division_by_zero_in_function_returns_undefined)
	{
		CCalculator calc;
		calc.SetVariableValue("x", 10.0);
		calc.SetVariableValue("y", 0.0);
		calc.DeclareFunction("div", "x", Operation::Divide, "y");
		auto value = calc.GetValue("div");
		BOOST_CHECK(!value.has_value());
	}

	BOOST_AUTO_TEST_CASE(get_all_variables_returns_sorted_by_name)
	{
		CCalculator calc;
		calc.SetVariableValue("b", 20.0);
		calc.SetVariableValue("a", 10.0);
		calc.DeclareVariable("c");

		auto vars = calc.GetAllVariables();
		BOOST_REQUIRE_EQUAL(vars.size(), 3);

		auto it = vars.begin();
		BOOST_CHECK_EQUAL(it->first, "a");
		BOOST_CHECK_EQUAL(it->second, 10.0);
		++it;
		BOOST_CHECK_EQUAL(it->first, "b");
		BOOST_CHECK_EQUAL(it->second, 20.0);
		++it;
		BOOST_CHECK_EQUAL(it->first, "c");
		BOOST_CHECK(std::isnan(it->second));
	}

	BOOST_AUTO_TEST_CASE(get_all_functions_returns_sorted_by_name)
	{
		CCalculator calc;
		calc.SetVariableValue("x", 10.0);
		calc.DeclareFunction("f2", "x");
		calc.DeclareFunction("f1", "x");

		auto funcs = calc.GetAllFunctions();
		BOOST_REQUIRE_EQUAL(funcs.size(), 2);

		auto it = funcs.begin();
		BOOST_CHECK_EQUAL(it->first, "f1");
		++it;
		BOOST_CHECK_EQUAL(it->first, "f2");
	}

	BOOST_AUTO_TEST_CASE(cannot_use_function_name_as_variable)
	{
		CCalculator calc;
		calc.SetVariableValue("x", 10.0);
		calc.DeclareFunction("f", "x");
		BOOST_CHECK(!calc.SetVariableValue("f", 20.0));
	}

	BOOST_AUTO_TEST_CASE(cannot_declare_duplicate_function)
	{
		CCalculator calc;
		calc.SetVariableValue("x", 10.0);
		calc.DeclareFunction("f", "x");
		BOOST_CHECK(!calc.DeclareFunction("f", "x"));
	}

	BOOST_AUTO_TEST_CASE(function_can_reference_another_function)
	{
		CCalculator calc;
		calc.SetVariableValue("x", 10.0);
		calc.DeclareFunction("f", "x");
		calc.DeclareFunction("g", "f");
		auto value = calc.GetValue("g");
		BOOST_REQUIRE(value.has_value());
		BOOST_CHECK_EQUAL(*value, 10.0);
	}

BOOST_AUTO_TEST_SUITE_END()