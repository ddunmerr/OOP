#include "CShapeFinder.h"
#include <algorithm>

CShapeFinder::CShapeFinder(std::vector<std::unique_ptr<IShape>>& shapes)
	: m_shapes(shapes)

{
}

IShape* CShapeFinder::FindShapeWithMaxArea() const
{
	if (m_shapes.empty())
	{
		return nullptr;
	}

	auto it = std::max_element(m_shapes.begin(), m_shapes.end(),
		[](const auto& a, const auto& b) {
			return a->GetArea() < b->GetArea();
		});

	return it->get();
}

IShape* CShapeFinder::FindShapeWithMinPerimeter() const
{
	if (m_shapes.empty())
	{
		return nullptr;
	}

	auto it = std::min_element(m_shapes.begin(), m_shapes.end(),
		[](const auto& a, const auto& b) {
			return a->GetPerimeter() < b->GetPerimeter();
		});

	return it->get();
}
