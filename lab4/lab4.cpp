#include "ShapeFinder.h"
#include "ShapeParser.h"
#include "consts.h"
#include <iostream>
#include <memory>
#include <vector>

int main()
{
	std::vector<std::unique_ptr<IShape>> shapes;
	std::string line;

	while (std::getline(std::cin, line))
	{
		if (line.empty())
		{
			continue;
		}

		auto shape = CShapeParser::ParseCommand(line);
		if (shape)
		{
			shapes.push_back(std::move(shape));
		}
		else
		{
			std::cout << ERROR_UNKNOWN_COMMAND << line << std::endl;
		}
	}

	if (!shapes.empty())
	{
		IShape* maxAreaShape = FindShapeWithMaxArea(shapes);
		IShape* minPerimeterShape = FindShapeWithMinPerimeter(shapes);

		std::cout << SHAPE_MAX_AREA << std::endl;
		std::cout << maxAreaShape->ToString() << std::endl;

		std::cout << SHAPE_MIN_AREA << std::endl;
		std::cout << minPerimeterShape->ToString() << std::endl;
	}
	else
	{
		std::cout << ERROR_NO_SHAPES << std::endl;
	}

	return 0;
}
