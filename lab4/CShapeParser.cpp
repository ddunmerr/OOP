#include "CCircle.h"
#include "CLineSegment.h"
#include "CPoint.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "CShapeParser.h"
#include <sstream>
#include <stdexcept>

uint32_t ParseColor(const std::string& hexStr)
{
	return static_cast<uint32_t>(std::stoul(hexStr, nullptr, 16));
}

std::unique_ptr<IShape> CShapeParser::ParseCommand(const std::string& line)
{
	std::istringstream iss(line);
	std::string shapeType;
	if (!(iss >> shapeType))
	{
		return nullptr;
	}

	if (shapeType == COMMAND_LINE)
	{
		double x1, y1, x2, y2;
		std::string colorStr;
		if (!(iss >> x1 >> y1 >> x2 >> y2 >> colorStr))
		{
			return nullptr;
		}
		CPoint start(x1, y1);
		CPoint end(x2, y2);
		uint32_t color = ParseColor(colorStr);

		return std::make_unique<CLineSegment>(start, end, color);
	}
	else if (shapeType == COMMAND_TRIANGLE)
	{
		double x1, y1, x2, y2, x3, y3;
		std::string outlineStr, fillStr;
		if (!(iss >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> outlineStr >> fillStr))
		{
			return nullptr;
		}
		CPoint v1(x1, y1), v2(x2, y2), v3(x3, y3);
		uint32_t outline = ParseColor(outlineStr);
		uint32_t fill = ParseColor(fillStr);

		return std::make_unique<CTriangle>(v1, v2, v3, outline, fill);
	}
	else if (shapeType == COMMAND_RECTANGLE)
	{
		double left, top, width, height;
		std::string outlineStr, fillStr;
		if (!(iss >> left >> top >> width >> height >> outlineStr >> fillStr))
		{
			return nullptr;
		}
		CPoint leftTop(left, top);
		uint32_t outline = ParseColor(outlineStr);
		uint32_t fill = ParseColor(fillStr);

		return std::make_unique<CRectangle>(leftTop, width, height, outline, fill);
	}
	else if (shapeType == COMMAND_CIRCLE)
	{
		double cx, cy, radius;
		std::string outlineStr, fillStr;
		if (!(iss >> cx >> cy >> radius >> outlineStr >> fillStr))
		{
			return nullptr;
		}
		CPoint center(cx, cy);
		uint32_t outline = ParseColor(outlineStr);
		uint32_t fill = ParseColor(fillStr);

		return std::make_unique<CCircle>(center, radius, outline, fill);
	}

	return nullptr;
}
