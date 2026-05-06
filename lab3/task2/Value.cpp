#include "Value.h"
#include <cmath>
#include <iomanip>
#include <sstream>

CValue::CValue()
	: m_value(std::nullopt)
{
}

CValue::CValue(double value)
	: m_value(value)
{
}

bool CValue::IsDefined() const
{
	return m_value.has_value();
}

double CValue::GetValue() const
{
	return m_value.value();
}

std::string CValue::ToString() const
{
	if (!m_value.has_value() || std::isnan(*m_value))
	{
		return "nan";
	}

	std::ostringstream oss;
	oss << std::fixed << std::setprecision(2) << *m_value;
	return oss.str();
}

CValue CValue::operator+(const CValue& other) const
{
	if (!m_value.has_value() || !other.m_value.has_value())
	{
		return CValue();
	}
	return CValue(*m_value + *other.m_value);
}

CValue CValue::operator-(const CValue& other) const
{
	if (!m_value.has_value() || !other.m_value.has_value())
	{
		return CValue();
	}
	return CValue(*m_value - *other.m_value);
}

CValue CValue::operator*(const CValue& other) const
{
	if (!m_value.has_value() || !other.m_value.has_value())
	{
		return CValue();
	}
	return CValue(*m_value * *other.m_value);
}

CValue CValue::operator/(const CValue& other) const
{
	if (!m_value.has_value() || !other.m_value.has_value())
	{
		return CValue();
	}
	if (*other.m_value == 0.0)
	{
		return CValue();
	}
	return CValue(*m_value / *other.m_value);
}
