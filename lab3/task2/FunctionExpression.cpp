#include "FunctionExpression.h"

CFunctionExpression::CFunctionExpression()
	: m_operand1("")
	, m_operand2("")
	, m_operation(Operation::None)
{
}

CFunctionExpression::CFunctionExpression(const std::string& operand1)
	: m_operand1(operand1)
	, m_operand2("")
	, m_operation(Operation::None)
{
}

CFunctionExpression::CFunctionExpression(const std::string& operand1, Operation op, const std::string& operand2)
	: m_operand1(operand1)
	, m_operand2(operand2)
	, m_operation(op)
{
}

std::optional<double> CFunctionExpression::Evaluate(
	std::function<std::optional<double>(const std::string&)> resolver) const
{
	auto val1 = resolver(m_operand1);

	if (!IsBinary())
	{
		return val1;
	}

	auto val2 = resolver(m_operand2);

	if (!val1.has_value() || !val2.has_value())
	{
		return std::nullopt;
	}

	switch (m_operation)
	{
	case Operation::Add:
		return *val1 + *val2;
	case Operation::Subtract:
		return *val1 - *val2;
	case Operation::Multiply:
		return *val1 * *val2;
	case Operation::Divide:
		if (*val2 == 0.0)
			return std::nullopt;
		return *val1 / *val2;
	default:
		return std::nullopt;
	}
}

bool CFunctionExpression::IsBinary() const
{
	return m_operation != Operation::None;
}

Operation CFunctionExpression::GetOperation() const
{
	return m_operation;
}

std::string CFunctionExpression::GetFirstOperand() const
{
	return m_operand1;
}

std::string CFunctionExpression::GetSecondOperand() const
{
	return m_operand2;
}