#pragma once
#include "IShape.h"
#include <vector>
#include <memory>

IShape* FindShapeWithMaxArea(const std::vector<std::unique_ptr<IShape>>& shapes);
IShape* FindShapeWithMinPerimeter(const std::vector<std::unique_ptr<IShape>>& shapes);