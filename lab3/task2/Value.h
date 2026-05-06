#pragma once
#include <optional>
#include <string>

class CValue
{
public:
	CValue();
	explicit CValue(double value);

	bool IsDefined() const;
	double GetValue() const;
	std::string ToString() const;

	CValue operator+(const CValue& other) const;
	CValue operator-(const CValue& other) const;
	CValue operator*(const CValue& other) const;
	CValue operator/(const CValue& other) const;

private:
	std::optional<double> m_value;
};