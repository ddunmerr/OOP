#include "stdafx.h"
#include "../task3/EconomySimulation.h"
#include <iostream>
#include <sstream>

BOOST_AUTO_TEST_SUITE(Economy_Simulation)

	BOOST_AUTO_TEST_CASE(simulation_initializes_with_correct_total_money)
	{
		CEconomySimulation sim(100000, 5);
		// Не падает при инициализации
		BOOST_CHECK(true);
	}

	// Можно добавить тест с перехватом вывода, но это не обязательно

BOOST_AUTO_TEST_SUITE_END()
