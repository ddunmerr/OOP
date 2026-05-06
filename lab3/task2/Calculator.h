#pragma once
#include "FunctionExpression.h"
#include <map>
#include <optional>
#include <string>

class CCalculator
{
public:
	CCalculator();

	// Команды
	bool DeclareVariable(const std::string& name);
	bool SetVariableValue(const std::string& name, double value);
	bool SetVariableValue(const std::string& name, const std::string& otherName);
	bool DeclareFunction(const std::string& name, const std::string& operand);
	bool DeclareFunction(const std::string& name, const std::string& operand1,
		Operation op, const std::string& operand2);

	// Запросы
	std::optional<double> GetValue(const std::string& name) const;
	std::string PrintIdentifier(const std::string& name) const;
	std::string PrintAllVariables() const;
	std::string PrintAllFunctions() const;

	// Вспомогательные
	bool HasIdentifier(const std::string& name) const;
	bool IsFunction(const std::string& name) const;
	bool IsVariable(const std::string& name) const;

	// Для тестов
	std::map<std::string, double> GetAllVariables() const;
	std::map<std::string, double> GetAllFunctions() const;

private:
	std::string FormatValue(const std::optional<double>& value) const;
	std::optional<double> ResolveIdentifier(const std::string& name) const;

	std::map<std::string, std::optional<double>> m_variables;
	std::map<std::string, CFunctionExpression> m_functions;
};