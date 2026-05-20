#define _USE_MATH_DEFINES
#include "CCircle.h"

CCircle::CCircle(const CPoint& center, double radius,
	uint32_t outlineColor, uint32_t fillColor)
	: m_center(center)
	, m_radius(radius)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

double CCircle::GetArea() const
{
	return M_PI * m_radius * m_radius;
}

double CCircle::GetPerimeter() const
{
	return 2.0 * M_PI * m_radius;
}

std::string CCircle::ToString() const
{
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(2)
		<< CIRCLE
		<< CENTER << m_center.ToString()
		<< RADIUS << m_radius
		<< AREA << GetArea()
		<< PERIMETER << GetPerimeter()
		<< OUTLINE_COLOR << std::hex << m_outlineColor
		<< FILL_COLOR << std::hex << m_fillColor;
	return oss.str();
}

uint32_t CCircle::GetOutlineColor() const { return m_outlineColor; }
uint32_t CCircle::GetFillColor() const { return m_fillColor; }
CPoint CCircle::GetCenter() const { return m_center; }
double CCircle::GetRadius() const { return m_radius; }
