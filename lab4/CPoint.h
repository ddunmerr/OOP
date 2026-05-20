#pragma once
#include "stdafx.h"
#include <string>

class CPoint
{
public:
	CPoint();
	CPoint(double x, double y);

	[[nodiscard]] double GetX() const;
	[[nodiscard]] double GetY() const;
	[[nodiscard]] std::string ToString() const;

private:
	double m_x = 0.0;
	double m_y = 0.0;
};
