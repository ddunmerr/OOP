#include "CommandParser.h"
#include <algorithm>
#include <regex>
#include <sstream>

CCommandParser::CCommandParser(CCalculator& calculator, std::ostream& output)
	: m_calculator(calculator)
	, m_output(output)
{
}

bool CCommandParser::ParseAndExecute(const std::string& line)
{
	std::string trimmed = Trim(line);
	if (trimmed.empty())
		return true;

	std::istringstream iss(trimmed);
	std::string command;
	iss >> command;

	if (command == "var")
		return HandleVar(iss);
	else if (command == "let")
		return HandleLet(trimmed);
	else if (command == "fn")
		return HandleFn(trimmed);
	else if (command == "print")
		return HandlePrint(iss);
	else if (command == "printvars")
		return HandlePrintVars();
	else if (command == "printfns")
		return HandlePrintFns();
	else
	{
		m_output << "Unknown command" << std::endl;
		return false;
	}
}

bool CCommandParser::IsValidIdentifier(const std::string& name)
{
	static const std::regex identifierRegex("^[a-zA-Z_][a-zA-Z0-9_]*$");
	return !name.empty() && std::regex_match(name, identifierRegex);
}

std::string CCommandParser::Trim(const std::string& str)
{
	size_t first = str.find_first_not_of(" \t");
	if (first == std::string::npos)
		return "";
	size_t last = str.find_last_not_of(" \t");
	return str.substr(first, last - first + 1);
}

bool CCommandParser::HandleVar(std::istream& args)
{
	std::string name;
	args >> name;

	if (!IsValidIdentifier(name))
	{
		m_output << "Invalid usage" << std::endl;
		return false;
	}

	if (!m_calculator.DeclareVariable(name))
	{
		m_output << "Name already exists" << std::endl;
		return false;
	}

	return true;
}

bool CCommandParser::HandleLet(const std::string& fullCommand)
{
	// let <id1> = <number>  или  let <id1> = <id2>
	static const std::regex letNumberRegex(
		R"(let\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*=\s*(-?\d+(?:\.\d+)?))");
	static const std::regex letIdentifierRegex(
		R"(let\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*=\s*([a-zA-Z_][a-zA-Z0-9_]*))");

	std::smatch match;

	if (std::regex_match(fullCommand, match, letNumberRegex))
	{
		std::string name = match[1];
		double value = std::stod(match[2]);

		if (!IsValidIdentifier(name) || m_calculator.IsFunction(name))
		{
			m_output << "Invalid usage" << std::endl;
			return false;
		}

		m_calculator.SetVariableValue(name, value);
		return true;
	}

	if (std::regex_match(fullCommand, match, letIdentifierRegex))
	{
		std::string name = match[1];
		std::string otherName = match[2];

		if (!IsValidIdentifier(name) || m_calculator.IsFunction(name))
		{
			m_output << "Invalid usage" << std::endl;
			return false;
		}

		if (!m_calculator.HasIdentifier(otherName))
		{
			m_output << "Name does not exist" << std::endl;
			return false;
		}

		m_calculator.SetVariableValue(name, otherName);
		return true;
	}

	m_output << "Invalid usage" << std::endl;
	return false;
}

bool CCommandParser::HandleFn(const std::string& fullCommand)
{
	// Удаляем все пробелы вокруг операторов для упрощения парсинга
	std::string normalized = fullCommand;
	// Удаляем пробелы вокруг +, -, *, /
	normalized = std::regex_replace(normalized, std::regex("\\s*([+\\-*/])\\s*"), "$1");
	// Нормализуем пробелы вокруг =
	normalized = std::regex_replace(normalized, std::regex("\\s*=\\s*"), "=");

	// fn <id1> = <id2> <op> <id3>
	static const std::regex fnBinaryRegex(
		R"(fn\s+([a-zA-Z_][a-zA-Z0-9_]*)=([a-zA-Z_][a-zA-Z0-9_]*)([+\-*/])([a-zA-Z_][a-zA-Z0-9_]*))");

	// fn <id1> = <id2>
	static const std::regex fnSimpleRegex(
		R"(fn\s+([a-zA-Z_][a-zA-Z0-9_]*)=([a-zA-Z_][a-zA-Z0-9_]*))");

	std::smatch match;

	if (std::regex_match(normalized, match, fnBinaryRegex))
	{
		std::string name = match[1];
		std::string operand1 = match[2];
		std::string opStr = match[3];
		std::string operand2 = match[4];

		if (!IsValidIdentifier(name))
		{
			m_output << "Invalid usage" << std::endl;
			return false;
		}

		if (m_calculator.HasIdentifier(name))
		{
			m_output << "Name already exists" << std::endl;
			return false;
		}

		if (!m_calculator.HasIdentifier(operand1) || !m_calculator.HasIdentifier(operand2))
		{
			m_output << "Name does not exist" << std::endl;
			return false;
		}

		Operation op;
		if (opStr == "+")
			op = Operation::Add;
		else if (opStr == "-")
			op = Operation::Subtract;
		else if (opStr == "*")
			op = Operation::Multiply;
		else if (opStr == "/")
			op = Operation::Divide;
		else
		{
			m_output << "Invalid usage" << std::endl;
			return false;
		}

		m_calculator.DeclareFunction(name, operand1, op, operand2);
		return true;
	}

	if (std::regex_match(normalized, match, fnSimpleRegex))
	{
		std::string name = match[1];
		std::string operand = match[2];

		if (!IsValidIdentifier(name))
		{
			m_output << "Invalid usage" << std::endl;
			return false;
		}

		if (m_calculator.HasIdentifier(name))
		{
			m_output << "Name already exists" << std::endl;
			return false;
		}

		if (!m_calculator.HasIdentifier(operand))
		{
			m_output << "Name does not exist" << std::endl;
			return false;
		}

		m_calculator.DeclareFunction(name, operand);
		return true;
	}

	m_output << "Invalid usage" << std::endl;
	return false;
}

bool CCommandParser::HandlePrint(std::istream& args)
{
	std::string name;
	args >> name;

	if (!IsValidIdentifier(name) || !m_calculator.HasIdentifier(name))
	{
		m_output << "Name does not exist" << std::endl;
		return false;
	}

	m_output << m_calculator.PrintIdentifier(name) << std::endl;
	return true;
}

bool CCommandParser::HandlePrintVars()
{
	m_output << m_calculator.PrintAllVariables();
	return true;
}

bool CCommandParser::HandlePrintFns()
{
	m_output << m_calculator.PrintAllFunctions();
	return true;
}