#pragma once
#include <functional>
#include <optional>
#include <string>

enum class Operation
{
	None,
	Add,
	Subtract,
	Multiply,
	Divide
};

class CFunctionExpression
{
public:
	CFunctionExpression();
	CFunctionExpression(const std::string& operand1);
	CFunctionExpression(const std::string& operand1, Operation op, const std::string& operand2);

	std::optional<double> Evaluate(
		std::function<std::optional<double>(const std::string&)> resolver) const;

	bool IsBinary() const;
	Operation GetOperation() const;
	std::string GetFirstOperand() const;
	std::string GetSecondOperand() const;

private:
	std::string m_operand1;
	std::string m_operand2;
	Operation m_operation;
};
