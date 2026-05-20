#pragma once
#include "IShape.h"
#include <memory>
#include <string>

class CShapeParser
{
public:
    static std::unique_ptr<IShape> ParseCommand(const std::string& line);
};