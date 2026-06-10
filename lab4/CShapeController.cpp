#include "CShapeController.h"
#include <iostream>

CShapeController::CShapeController(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
{
}

void CShapeController::Run()
{

	if (ReadShapes())
	{
		PrintResults();
	}
	else
	{
		m_output << ERROR_NO_SHAPES << std::endl;
	}
}

bool CShapeController::ReadShapes()
{
	std::string line;

	while (std::getline(m_input, line))
	{
		if (line.empty())
		{
			continue;
		}

		auto shape = CShapeParser::ParseCommand(line);
		if (shape)
		{
			m_shapes.push_back(std::move(shape));
		}
		else
		{
			m_output << ERROR_UNKNOWN_COMMAND << line << std::endl;
		}
	}

	return !m_shapes.empty();
}

void CShapeController::PrintResults() const
{
	CShapeFinder finder(m_shapes);

	const IShape* maxAreaShape = finder.FindShapeWithMaxArea();
	const IShape* minPerimeterShape = finder.FindShapeWithMinPerimeter();

	m_output << SHAPE_MAX_AREA << std::endl;
	m_output << maxAreaShape->ToString() << std::endl;

	m_output << SHAPE_MIN_AREA << std::endl;
	m_output << minPerimeterShape->ToString() << std::endl;
}
