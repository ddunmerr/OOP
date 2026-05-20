#pragma once
#include "stdafx.h"
#include "CPoint.h"
#include "ISolidShape.h"

class CRectangle : public ISolidShape
{
public:
	CRectangle(const CPoint& leftTop, double width, double height,
		uint32_t outlineColor, uint32_t fillColor);

	[[nodiscard]] double GetArea() const override;
	[[nodiscard]] double GetPerimeter() const override;
	[[nodiscard]] std::string ToString() const override;
	[[nodiscard]] uint32_t GetOutlineColor() const override;
	[[nodiscard]] uint32_t GetFillColor() const override;

	[[nodiscard]] CPoint GetLeftTop() const;
	[[nodiscard]] CPoint GetRightBottom() const;
	[[nodiscard]] double GetWidth() const;
	[[nodiscard]] double GetHeight() const;

private:
	CPoint m_leftTop;
	double m_width;
	double m_height;
	uint32_t m_outlineColor;
	uint32_t m_fillColor;
};
