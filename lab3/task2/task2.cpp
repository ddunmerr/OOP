//#include "stdafx.h"
#include "Calculator.h"
#include "CommandParser.h"

#include <iostream>

int main()
{
	CCalculator calculator;
	CCommandParser parser(calculator, std::cout);

	std::string line;
	while (std::getline(std::cin, line))
	{
		parser.ParseAndExecute(line);
	}

	return 0;
}