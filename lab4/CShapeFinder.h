#pragma once
#include "IShape.h"
#include <memory>
#include <vector>

class CShapeFinder
{
public:
	CShapeFinder(std::vector<std::unique_ptr<IShape>>& shapes);

	IShape* FindShapeWithMaxArea() const;
	IShape* FindShapeWithMinPerimeter() const;

private:
	std::vector<std::unique_ptr<IShape>>& m_shapes;
};
