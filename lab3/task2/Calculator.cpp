#include "Calculator.h"
#include <cmath>
#include <iomanip>
#include <sstream>

CCalculator::CCalculator() = default;

bool CCalculator::DeclareVariable(const std::string& name)
{
	if (HasIdentifier(name))
		return false;
	m_variables[name] = std::nullopt;
	return true;
}

bool CCalculator::SetVariableValue(const std::string& name, double value)
{
	if (IsFunction(name))
		return false;
	m_variables[name] = value;
	return true;
}

bool CCalculator::SetVariableValue(const std::string& name, const std::string& otherName)
{
	if (IsFunction(name))
		return false;

	auto otherValue = ResolveIdentifier(otherName);
	if (!otherValue.has_value() && !HasIdentifier(otherName))
		return false; // Идентификатор не существует

	m_variables[name] = otherValue;
	return true;
}

bool CCalculator::DeclareFunction(const std::string& name, const std::string& operand)
{
	if (HasIdentifier(name))
		return false;
	m_functions[name] = CFunctionExpression(operand);
	return true;
}

bool CCalculator::DeclareFunction(const std::string& name, const std::string& operand1,
	Operation op, const std::string& operand2)
{
	if (HasIdentifier(name))
		return false;
	m_functions[name] = CFunctionExpression(operand1, op, operand2);
	return true;
}

std::optional<double> CCalculator::GetValue(const std::string& name) const
{
	return ResolveIdentifier(name);
}

std::string CCalculator::FormatValue(const std::optional<double>& value) const
{
	if (!value.has_value() || std::isnan(*value))
		return "nan";

	std::ostringstream oss;
	oss << std::fixed << std::setprecision(2) << *value;
	return oss.str();
}

std::string CCalculator::PrintIdentifier(const std::string& name) const
{
	auto value = ResolveIdentifier(name);
	return FormatValue(value);
}

std::string CCalculator::PrintAllVariables() const
{
	std::ostringstream result;
	for (const auto& [name, value] : m_variables)
	{
		double displayValue = value.value_or(std::numeric_limits<double>::quiet_NaN());
		result << name << ":" << FormatValue(value) << "\n";
	}
	return result.str();
}

std::string CCalculator::PrintAllFunctions() const
{
	std::ostringstream result;
	for (const auto& [name, expr] : m_functions)
	{
		auto value = ResolveIdentifier(name);
		result << name << ":" << FormatValue(value) << "\n";
	}
	return result.str();
}

std::map<std::string, double> CCalculator::GetAllVariables() const
{
	std::map<std::string, double> result;
	for (const auto& [name, value] : m_variables)
	{
		result[name] = value.value_or(std::numeric_limits<double>::quiet_NaN());
	}
	return result;
}

std::map<std::string, double> CCalculator::GetAllFunctions() const
{
	std::map<std::string, double> result;
	for (const auto& [name, expr] : m_functions)
	{
		auto val = ResolveIdentifier(name);
		result[name] = val.value_or(std::numeric_limits<double>::quiet_NaN());
	}
	return result;
}

bool CCalculator::HasIdentifier(const std::string& name) const
{
	return IsVariable(name) || IsFunction(name);
}

bool CCalculator::IsFunction(const std::string& name) const
{
	return m_functions.find(name) != m_functions.end();
}

bool CCalculator::IsVariable(const std::string& name) const
{
	return m_variables.find(name) != m_variables.end();
}

std::optional<double> CCalculator::ResolveIdentifier(const std::string& name) const
{
	auto varIt = m_variables.find(name);
	if (varIt != m_variables.end())
	{
		return varIt->second;
	}

	auto funcIt = m_functions.find(name);
	if (funcIt != m_functions.end())
	{
		return funcIt->second.Evaluate(
			[this](const std::string& n) { return ResolveIdentifier(n); });
	}

	return std::nullopt;
}