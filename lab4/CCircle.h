#pragma once
#include "stdafx.h"
#include "CPoint.h"
#include "ISolidShape.h"

class CCircle : public ISolidShape
{
public:
	CCircle(const CPoint& center, double radius,
		uint32_t outlineColor, uint32_t fillColor);

	[[nodiscard]] double GetArea() const override;
	[[nodiscard]] double GetPerimeter() const override;
	[[nodiscard]] std::string ToString() const override;
	[[nodiscard]] uint32_t GetOutlineColor() const override;
	[[nodiscard]] uint32_t GetFillColor() const override;

	[[nodiscard]] CPoint GetCenter() const;
	[[nodiscard]] double GetRadius() const;

private:
	CPoint m_center;
	double m_radius;
	uint32_t m_outlineColor;
	uint32_t m_fillColor;
};
