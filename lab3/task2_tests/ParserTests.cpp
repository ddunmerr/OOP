#include "stdafx.h"
#include "../task2/Calculator.h"
#include <sstream>

// Тут тесты парсинга команд
// Проверяют формат вывода и обработку ошибок
BOOST_AUTO_TEST_SUITE(CommandParsing)

	// Тест: var x — объявление переменной
	// Тест: let x = 42.5 — присваивание числа
	// Тест: let x = y — присваивание значения другой переменной
	// Тест: fn f = x — объявление простой функции
	// Тест: fn f = x + y — объявление бинарной функции
	// Тест: print x — вывод значения
	// Тест: printvars — вывод всех переменных
	// Тест: printfns — вывод всех функций
	// Тест: неизвестная команда → "Unknown command"
	// Тест: неверный синтаксис → "Invalid usage"
	// Тест: дубликат имени → "Name already exists"
	// Тест: несуществующее имя → "Name does not exist"
	// Тест: слитная запись fn f=x+y
	// Тест: запись с пробелами fn f = x + y

BOOST_AUTO_TEST_SUITE_END()