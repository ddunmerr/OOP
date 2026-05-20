#include "CPoint.h"

CPoint::CPoint() = default;

CPoint::CPoint(double x, double y)
	: m_x(x)
	, m_y(y)
{
}

double CPoint::GetX() const
{
	return m_x;
}

double CPoint::GetY() const
{
	return m_y;
}

std::string CPoint::ToString() const
{
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(2)
		<< "(" << m_x << ", " << m_y << ")";
	return oss.str();
}
