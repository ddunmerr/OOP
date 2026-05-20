#pragma once
#include "stdafx.h"
#include "CPoint.h"
#include "IShape.h"

class CLineSegment : public IShape
{
public:
	CLineSegment(const CPoint& startPoint, const CPoint& endPoint, uint32_t outlineColor);

	[[nodiscard]] double GetArea() const override;
	[[nodiscard]] double GetPerimeter() const override;
	[[nodiscard]] std::string ToString() const override;
	[[nodiscard]] uint32_t GetOutlineColor() const override;

	[[nodiscard]] CPoint GetStartPoint() const;
	[[nodiscard]] CPoint GetEndPoint() const;

private:
	CPoint m_startPoint;
	CPoint m_endPoint;
	uint32_t m_outlineColor;
};
