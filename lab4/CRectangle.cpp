#include "CRectangle.h"

CRectangle::CRectangle(const CPoint& leftTop, double width, double height,
	uint32_t outlineColor, uint32_t fillColor)
	: m_leftTop(leftTop)
	, m_width(width)
	, m_height(height)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

double CRectangle::GetArea() const
{
	return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
	return 2.0 * (m_width + m_height);
}

std::string CRectangle::ToString() const
{
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(2)
		<< RECTANGLE
		<< LEFT_TOP << m_leftTop.ToString()
		<< WIDTH << m_width
		<< HEIGHT << m_height
		<< AREA << GetArea()
		<< PERIMETER << GetPerimeter()
		<< OUTLINE_COLOR << std::hex << m_outlineColor
		<< FILL_COLOR << std::hex << m_fillColor;
	return oss.str();
}

uint32_t CRectangle::GetOutlineColor() const { return m_outlineColor; }
uint32_t CRectangle::GetFillColor() const { return m_fillColor; }
CPoint CRectangle::GetLeftTop() const { return m_leftTop; }

CPoint CRectangle::GetRightBottom() const
{
	return CPoint(m_leftTop.GetX() + m_width, m_leftTop.GetY() - m_height);
}

double CRectangle::GetWidth() const { return m_width; }
double CRectangle::GetHeight() const { return m_height; }
