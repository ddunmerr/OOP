#pragma once
#include "Calculator.h"
#include <iosfwd>

class CCommandParser
{
public:
	CCommandParser(CCalculator& calculator, std::ostream& output);

	bool ParseAndExecute(const std::string& line);

	static bool IsValidIdentifier(const std::string& name);

private:
	std::string Trim(const std::string& str);

	bool HandleVar(std::istream& args);
	bool HandleLet(const std::string& fullCommand);
	bool HandleFn(const std::string& fullCommand);
	bool HandlePrint(std::istream& args);
	bool HandlePrintVars();
	bool HandlePrintFns();

	CCalculator& m_calculator;
	std::ostream& m_output;
};