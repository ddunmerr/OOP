#include "stdafx.h"
#include "../Lab5/CTime.h"
#include <sstream>

BOOST_AUTO_TEST_SUITE(CTime_construction)
	// Конструктор по умолчанию создаёт полночь (00:00:00)
	BOOST_AUTO_TEST_CASE(default_constructor_creates_midnight)
	{
		CTime time;
		BOOST_CHECK(time.IsValid());
		BOOST_CHECK_EQUAL(time.GetHours(), 0u);
		BOOST_CHECK_EQUAL(time.GetMinutes(), 0u);
		BOOST_CHECK_EQUAL(time.GetSeconds(), 0u);
	}

	// Конструктор с тремя аргументами корректно устанавливает часы, минуты и секунды
	BOOST_AUTO_TEST_CASE(three_arg_constructor_valid_time)
	{
		CTime time(14, 30, 25);
		BOOST_CHECK(time.IsValid());
		BOOST_CHECK_EQUAL(time.GetHours(), 14u);
		BOOST_CHECK_EQUAL(time.GetMinutes(), 30u);
		BOOST_CHECK_EQUAL(time.GetSeconds(), 25u);
	}

	// Часы больше 23 делают время невалидным
	BOOST_AUTO_TEST_CASE(three_arg_constructor_invalid_hours)
	{
		CTime time(25, 0, 0);
		BOOST_CHECK(!time.IsValid());
	}

	// Минуты больше 59 делают время невалидным
	BOOST_AUTO_TEST_CASE(three_arg_constructor_invalid_minutes)
	{
		CTime time(10, 60, 0);
		BOOST_CHECK(!time.IsValid());
	}

	// Секунды больше 59 делают время невалидным
	BOOST_AUTO_TEST_CASE(three_arg_constructor_invalid_seconds)
	{
		CTime time(10, 30, 60);
		BOOST_CHECK(!time.IsValid());
	}

	// Timestamp-конструктор переводит секунды в часы, минуты и секунды
	BOOST_AUTO_TEST_CASE(timestamp_constructor_seconds_to_time)
	{
		CTime time(3725);
		BOOST_CHECK(time.IsValid());
		BOOST_CHECK_EQUAL(time.GetHours(), 1u);
		BOOST_CHECK_EQUAL(time.GetMinutes(), 2u);
		BOOST_CHECK_EQUAL(time.GetSeconds(), 5u);
	}

	// Timestamp-конструктор зацикливает значение при выходе за границы суток
	BOOST_AUTO_TEST_CASE(timestamp_constructor_wraps_around_midnight)
	{
		CTime time(90000);
		BOOST_CHECK_EQUAL(time.GetHours(), 1u);
		BOOST_CHECK_EQUAL(time.GetMinutes(), 0u);
		BOOST_CHECK_EQUAL(time.GetSeconds(), 0u);
	}

	// Конструктор с двумя аргументами устанавливает секунды в ноль по умолчанию
	BOOST_AUTO_TEST_CASE(three_arg_constructor_default_seconds)
	{
		CTime time(10, 30, 0);
		BOOST_CHECK(time.IsValid());
		BOOST_CHECK_EQUAL(time.GetSeconds(), 0u);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CTime_arithmetic)
	// Префиксный инкремент увеличивает время на 1 секунду
	BOOST_AUTO_TEST_CASE(prefix_increment)
	{
		CTime time(0, 0, 0);
		++time;
		BOOST_CHECK_EQUAL(time.GetTotalSeconds(), 1u);
	}

	// Постфиксный инкремент возвращает старое значение и увеличивает время на 1 секунду
	BOOST_AUTO_TEST_CASE(postfix_increment)
	{
		CTime time(0, 0, 0);
		CTime old = time++;
		BOOST_CHECK_EQUAL(old.GetTotalSeconds(), 0u);
		BOOST_CHECK_EQUAL(time.GetTotalSeconds(), 1u);
	}

	// Инкремент в 23:59:59 переводит время на 00:00:00
	BOOST_AUTO_TEST_CASE(increment_wraps_at_midnight)
	{
		CTime time(23, 59, 59);
		++time;
		BOOST_CHECK_EQUAL(time.GetHours(), 0u);
		BOOST_CHECK_EQUAL(time.GetMinutes(), 0u);
		BOOST_CHECK_EQUAL(time.GetSeconds(), 0u);
	}

	// Префиксный декремент уменьшает время на 1 секунду
	BOOST_AUTO_TEST_CASE(prefix_decrement)
	{
		CTime time(0, 0, 5);
		--time;
		BOOST_CHECK_EQUAL(time.GetTotalSeconds(), 4u);
	}

	// Декремент в 00:00:00 переводит время на 23:59:59
	BOOST_AUTO_TEST_CASE(decrement_wraps_at_midnight)
	{
		CTime time(0, 0, 0);
		--time;
		BOOST_CHECK_EQUAL(time.GetHours(), 23u);
		BOOST_CHECK_EQUAL(time.GetMinutes(), 59u);
		BOOST_CHECK_EQUAL(time.GetSeconds(), 59u);
	}

	// Сложение двух валидных времён без перехода через полночь
	BOOST_AUTO_TEST_CASE(addition_two_valid_times)
	{
		CTime t1(14, 30, 25);
		CTime t2(3, 18, 44);
		CTime result = t1 + t2;
		BOOST_CHECK_EQUAL(result.GetHours(), 17u);
		BOOST_CHECK_EQUAL(result.GetMinutes(), 49u);
		BOOST_CHECK_EQUAL(result.GetSeconds(), 9u);
	}

	// Сложение с переходом через полночь
	BOOST_AUTO_TEST_CASE(addition_wraps_around_midnight)
	{
		CTime t1(23, 59, 59);
		CTime t2(0, 0, 3);
		CTime result = t1 + t2;
		BOOST_CHECK_EQUAL(result.GetHours(), 0u);
		BOOST_CHECK_EQUAL(result.GetMinutes(), 0u);
		BOOST_CHECK_EQUAL(result.GetSeconds(), 2u);
	}

	// Вычитание двух валидных времён без перехода через полночь
	BOOST_AUTO_TEST_CASE(subtraction_normal)
	{
		CTime t1(14, 30, 25);
		CTime t2(3, 18, 44);
		CTime result = t1 - t2;
		BOOST_CHECK_EQUAL(result.GetHours(), 11u);
		BOOST_CHECK_EQUAL(result.GetMinutes(), 11u);
		BOOST_CHECK_EQUAL(result.GetSeconds(), 41u);
	}

	// Вычитание с переходом через полночь
	BOOST_AUTO_TEST_CASE(subtraction_wraps_around_midnight)
	{
		CTime t1(0, 0, 5);
		CTime t2(0, 0, 10);
		CTime result = t1 - t2;
		BOOST_CHECK_EQUAL(result.GetHours(), 23u);
		BOOST_CHECK_EQUAL(result.GetMinutes(), 59u);
		BOOST_CHECK_EQUAL(result.GetSeconds(), 55u);
	}

	// Оператор += увеличивает время на заданное значение
	BOOST_AUTO_TEST_CASE(plus_equal)
	{
		CTime time(10, 0, 0);
		time += CTime(2, 30, 0);
		BOOST_CHECK_EQUAL(time.GetHours(), 12u);
		BOOST_CHECK_EQUAL(time.GetMinutes(), 30u);
	}

	// Оператор -= уменьшает время на заданное значение
	BOOST_AUTO_TEST_CASE(minus_equal)
	{
		CTime time(10, 0, 0);
		time -= CTime(2, 30, 0);
		BOOST_CHECK_EQUAL(time.GetHours(), 7u);
		BOOST_CHECK_EQUAL(time.GetMinutes(), 30u);
	}

	// Умножение времени на целое число
	BOOST_AUTO_TEST_CASE(multiply_by_unsigned)
	{
		CTime time(3, 5, 15);
		CTime result = time * 3;
		BOOST_CHECK_EQUAL(result.GetHours(), 9u);
		BOOST_CHECK_EQUAL(result.GetMinutes(), 15u);
		BOOST_CHECK_EQUAL(result.GetSeconds(), 45u);
	}

	// Умножение целого числа на время (коммутативность)
	BOOST_AUTO_TEST_CASE(unsigned_multiply_time)
	{
		CTime time(3, 5, 15);
		CTime result = 3 * time;
		BOOST_CHECK_EQUAL(result.GetHours(), 9u);
		BOOST_CHECK_EQUAL(result.GetMinutes(), 15u);
		BOOST_CHECK_EQUAL(result.GetSeconds(), 45u);
	}

	// Умножение времени с переходом через полночь
	BOOST_AUTO_TEST_CASE(multiply_wraps_around_midnight)
	{
		CTime time(10, 0, 0);
		CTime result = time * 3;
		BOOST_CHECK_EQUAL(result.GetHours(), 6u);
	}

	// Оператор *= умножает время на целое число
	BOOST_AUTO_TEST_CASE(multiply_equal)
	{
		CTime time(1, 30, 0);
		time *= 2;
		BOOST_CHECK_EQUAL(time.GetHours(), 3u);
	}

	// Деление времени на целое число
	BOOST_AUTO_TEST_CASE(divide_by_unsigned)
	{
		CTime time(9, 15, 40);
		CTime result = time / 3;
		BOOST_CHECK_EQUAL(result.GetHours(), 3u);
		BOOST_CHECK_EQUAL(result.GetMinutes(), 5u);
		BOOST_CHECK_EQUAL(result.GetSeconds(), 13u);
	}

	// Деление времени на время возвращает целое количество
	BOOST_AUTO_TEST_CASE(divide_time_by_time)
	{
		CTime t1(9, 15, 40);
		CTime t2(3, 5, 13);
		unsigned result = t1 / t2;
		BOOST_CHECK_EQUAL(result, 3u);
	}

	// Оператор /= делит время на целое число
	BOOST_AUTO_TEST_CASE(divide_equal)
	{
		CTime time(6, 0, 0);
		time /= 2;
		BOOST_CHECK_EQUAL(time.GetHours(), 3u);
	}

	// Деление на ноль возвращает невалидное время
	BOOST_AUTO_TEST_CASE(divide_by_zero_returns_invalid)
	{
		CTime time(10, 0, 0);
		CTime result = time / 0;
		BOOST_CHECK(!result.IsValid());
	}

	// Операции с невалидным операндом возвращают невалидное время
	BOOST_AUTO_TEST_CASE(invalid_operand_returns_invalid)
	{
		CTime invalid(25, 0, 0);
		CTime valid(10, 0, 0);

		BOOST_CHECK(!(invalid + valid).IsValid());
		BOOST_CHECK(!(valid + invalid).IsValid());
		BOOST_CHECK(!(invalid * 2).IsValid());
		BOOST_CHECK(!(invalid / 2).IsValid());
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CTime_comparison)
	// Одинаковые времена равны
	BOOST_AUTO_TEST_CASE(equal_times)
	{
		CTime t1(10, 30, 45);
		CTime t2(10, 30, 45);
		BOOST_CHECK(t1 == t2);
		BOOST_CHECK(!(t1 != t2));
	}

	// Времена с разницей в 1 секунду не равны
	BOOST_AUTO_TEST_CASE(not_equal_times)
	{
		CTime t1(10, 30, 45);
		CTime t2(10, 30, 46);
		BOOST_CHECK(t1 != t2);
	}

	// Раннее время меньше более позднего
	BOOST_AUTO_TEST_CASE(less_than)
	{
		CTime t1(10, 30, 0);
		CTime t2(10, 30, 1);
		BOOST_CHECK(t1 < t2);
	}

	// Позднее время больше раннего
	BOOST_AUTO_TEST_CASE(greater_than)
	{
		CTime t1(10, 30, 2);
		CTime t2(10, 30, 1);
		BOOST_CHECK(t1 > t2);
	}

	// Нестрогое меньше или равно
	BOOST_AUTO_TEST_CASE(less_or_equal)
	{
		CTime t1(10, 30, 0);
		CTime t2(10, 30, 0);
		CTime t3(10, 30, 1);
		BOOST_CHECK(t1 <= t2);
		BOOST_CHECK(t1 <= t3);
	}

	// Нестрогое больше или равно
	BOOST_AUTO_TEST_CASE(greater_or_equal)
	{
		CTime t1(10, 30, 2);
		CTime t2(10, 30, 2);
		CTime t3(10, 30, 1);
		BOOST_CHECK(t1 >= t2);
		BOOST_CHECK(t1 >= t3);
	}

	// Сравнение с невалидным временем всегда возвращает false
	BOOST_AUTO_TEST_CASE(comparison_with_invalid)
	{
		CTime invalid(25, 0, 0);
		CTime valid(10, 0, 0);
		BOOST_CHECK(!(invalid < valid));
		BOOST_CHECK(!(valid < invalid));
		BOOST_CHECK(!(invalid > valid));
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CTime_io)
	// Вывод валидного времени в формате ЧЧ:ММ:СС
	BOOST_AUTO_TEST_CASE(output_valid_time)
	{
		CTime time(14, 30, 25);
		std::ostringstream oss;
		oss << time;
		BOOST_CHECK_EQUAL(oss.str(), "14:30:25");
	}

	// Вывод невалидного времени выводит строку INVALID
	BOOST_AUTO_TEST_CASE(output_invalid_time)
	{
		CTime time(25, 0, 0);
		std::ostringstream oss;
		oss << time;
		BOOST_CHECK_EQUAL(oss.str(), "INVALID");
	}

	// Вывод времени с ведущими нулями для однозначных чисел
	BOOST_AUTO_TEST_CASE(output_with_leading_zeros)
	{
		CTime time(1, 5, 9);
		std::ostringstream oss;
		oss << time;
		BOOST_CHECK_EQUAL(oss.str(), "01:05:09");
	}

	// Ввод валидного времени из потока в формате ЧЧ:ММ:СС
	BOOST_AUTO_TEST_CASE(input_valid_time)
	{
		std::istringstream iss("14:30:25");
		CTime time;
		iss >> time;
		BOOST_CHECK(time.IsValid());
		BOOST_CHECK_EQUAL(time.GetHours(), 14u);
		BOOST_CHECK_EQUAL(time.GetMinutes(), 30u);
		BOOST_CHECK_EQUAL(time.GetSeconds(), 25u);
	}

	// Ввод строки неверного формата устанавливает флаг ошибки потока
	BOOST_AUTO_TEST_CASE(input_invalid_format_sets_failbit)
	{
		std::istringstream iss("invalid");
		CTime time;
		iss >> time;
		BOOST_CHECK(iss.fail());
	}
BOOST_AUTO_TEST_SUITE_END()
