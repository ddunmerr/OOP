#include "stdafx.h"
#include "../task2/Value.h"

BOOST_AUTO_TEST_SUITE(Value)

	BOOST_AUTO_TEST_CASE(default_value_is_undefined)
	{
		CValue v;
		BOOST_CHECK(!v.IsDefined());
		BOOST_CHECK_EQUAL(v.ToString(), "nan");
	}

	BOOST_AUTO_TEST_CASE(can_be_constructed_from_double)
	{
		CValue v(42.5);
		BOOST_CHECK(v.IsDefined());
		BOOST_CHECK_EQUAL(v.GetValue(), 42.5);
	}

	BOOST_AUTO_TEST_CASE(addition_of_two_defined_values)
	{
		CValue a(10.0);
		CValue b(20.0);
		CValue result = a + b;
		BOOST_CHECK(result.IsDefined());
		BOOST_CHECK_EQUAL(result.GetValue(), 30.0);
	}

	BOOST_AUTO_TEST_CASE(addition_with_undefined_returns_undefined)
	{
		CValue a(10.0);
		CValue b;
		CValue result = a + b;
		BOOST_CHECK(!result.IsDefined());
	}

	BOOST_AUTO_TEST_CASE(subtraction_works_correctly)
	{
		CValue a(50.0);
		CValue b(20.0);
		CValue result = a - b;
		BOOST_CHECK_EQUAL(result.GetValue(), 30.0);
	}

	BOOST_AUTO_TEST_CASE(multiplication_works_correctly)
	{
		CValue a(7.0);
		CValue b(8.0);
		CValue result = a * b;
		BOOST_CHECK_EQUAL(result.GetValue(), 56.0);
	}

	BOOST_AUTO_TEST_CASE(division_works_correctly)
	{
		CValue a(100.0);
		CValue b(4.0);
		CValue result = a / b;
		BOOST_CHECK_EQUAL(result.GetValue(), 25.0);
	}

	BOOST_AUTO_TEST_CASE(division_by_zero_returns_undefined)
	{
		CValue a(10.0);
		CValue b(0.0);
		CValue result = a / b;
		BOOST_CHECK(!result.IsDefined());
	}

	BOOST_AUTO_TEST_CASE(division_with_undefined_returns_undefined)
	{
		CValue a(10.0);
		CValue b;
		CValue result = a / b;
		BOOST_CHECK(!result.IsDefined());
	}

	BOOST_AUTO_TEST_CASE(to_string_formats_to_two_decimals)
	{
		CValue v(3.14159);
		BOOST_CHECK_EQUAL(v.ToString(), "3.14");
	}

	BOOST_AUTO_TEST_CASE(to_string_rounds_correctly)
	{
		CValue v(3.456);
		BOOST_CHECK_EQUAL(v.ToString(), "3.46");
	}

BOOST_AUTO_TEST_SUITE_END()