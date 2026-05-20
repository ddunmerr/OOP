#pragma once
#include "stdafx.h"
#include "CPoint.h"
#include "ISolidShape.h"

class CTriangle : public ISolidShape
{
public:
	CTriangle(const CPoint& vertex1, const CPoint& vertex2, const CPoint& vertex3,
		uint32_t outlineColor, uint32_t fillColor);

	[[nodiscard]] double GetArea() const override;
	[[nodiscard]] double GetPerimeter() const override;
	[[nodiscard]] std::string ToString() const override;
	[[nodiscard]] uint32_t GetOutlineColor() const override;
	[[nodiscard]] uint32_t GetFillColor() const override;

	[[nodiscard]] CPoint GetVertex1() const;
	[[nodiscard]] CPoint GetVertex2() const;
	[[nodiscard]] CPoint GetVertex3() const;

private:
	[[nodiscard]] double GetSideLength(const CPoint& point1, const CPoint& point2) const;

	CPoint m_vertex1;
	CPoint m_vertex2;
	CPoint m_vertex3;
	uint32_t m_outlineColor;
	uint32_t m_fillColor;
};
