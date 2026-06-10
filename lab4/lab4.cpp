#include "CShapeController.h"
#include "CShapeFinder.h"
#include "CShapeParser.h"
#include "consts.h"
#include <iostream>
#include <memory>
#include <vector>

int main()
{
	CShapeController controller(std::cin, std::cout);
	controller.Run();
}
