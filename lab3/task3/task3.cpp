#include "EconomySimulation.h"
// #include <cstdlib>
// #include <iostream>

int main(int argc, char* argv[])
{
	int iterations = 0;

	if (argc > 1)
	{
		iterations = std::atoi(argv[1]);
	}
	else
	{
		std::cout << ENTER_ITERATIONS;
		std::cin >> iterations;
	}

	if (iterations <= 0)
	{
		std::cout << ERROR_INVALID_NUMBER_OF_ITERATIONS << std::endl;
		return 1;
	}

	const Money initialCash = 100000;
	CEconomySimulation simulation(initialCash, iterations);
	simulation.Run();

	return 0;
}
