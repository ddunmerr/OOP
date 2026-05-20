#include "CLineSegment.h"

CLineSegment::CLineSegment(const CPoint& startPoint, const CPoint& endPoint, uint32_t outlineColor)
	: m_startPoint(startPoint)
	, m_endPoint(endPoint)
	, m_outlineColor(outlineColor)
{
}

double CLineSegment::GetArea() const
{
	return 0.0;
}

double CLineSegment::GetPerimeter() const
{
	double dx = m_endPoint.GetX() - m_startPoint.GetX();
	double dy = m_endPoint.GetY() - m_startPoint.GetY();
	return std::sqrt(dx * dx + dy * dy);
}

std::string CLineSegment::ToString() const
{
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(2)
		<< LINE_SEGMENT
		<< m_startPoint.ToString() << " -> " << m_endPoint.ToString()
		<< OUTLINE_COLOR << std::hex << m_outlineColor;
	return oss.str();
}

uint32_t CLineSegment::GetOutlineColor() const
{
	return m_outlineColor;
}

CPoint CLineSegment::GetStartPoint() const
{
	return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_endPoint;
}
