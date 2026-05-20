#include "stdafx.h"
#include "../lab4/CPoint.h"
#include "../lab4/CLineSegment.h"
#include "../lab4/CTriangle.h"
#include "../lab4/CRectangle.h"
#include "../lab4/CCircle.h"
#include "../lab4/ShapeParser.h"
#include "../lab4/ShapeFinder.h"

BOOST_AUTO_TEST_SUITE(Shapes)

BOOST_AUTO_TEST_CASE(point_creation)
{
    CPoint p(3.5, -2.0);
    BOOST_CHECK_EQUAL(p.GetX(), 3.5);
    BOOST_CHECK_EQUAL(p.GetY(), -2.0);
}

BOOST_AUTO_TEST_CASE(line_segment_perimeter)
{
    CLineSegment line(CPoint(0, 0), CPoint(3, 4), 0x000000);
    BOOST_CHECK_EQUAL(line.GetPerimeter(), 5.0);
    BOOST_CHECK_EQUAL(line.GetArea(), 0.0);
}

BOOST_AUTO_TEST_CASE(triangle_area)
{
    CTriangle triangle(CPoint(0, 0), CPoint(4, 0), CPoint(0, 3), 0x000000, 0xFFFFFF);
    BOOST_CHECK_EQUAL(triangle.GetArea(), 6.0);
    BOOST_CHECK_CLOSE(triangle.GetPerimeter(), 12.0, 0.01);
}

BOOST_AUTO_TEST_CASE(rectangle_area)
{
    CRectangle rect(CPoint(0, 10), 5, 10, 0x000000, 0xFFFFFF);
    BOOST_CHECK_EQUAL(rect.GetArea(), 50.0);
    BOOST_CHECK_EQUAL(rect.GetPerimeter(), 30.0);
}

BOOST_AUTO_TEST_CASE(circle_area)
{
    CCircle circle(CPoint(0, 0), 5, 0x000000, 0xFFFFFF);
    BOOST_CHECK_CLOSE(circle.GetArea(), 78.5398, 0.01);
    BOOST_CHECK_CLOSE(circle.GetPerimeter(), 31.4159, 0.01);
}

BOOST_AUTO_TEST_CASE(factory_parse_line)
{
    auto shape = CShapeParser::ParseCommand("line 0 0 3 4 000000");
    BOOST_REQUIRE(shape != nullptr);
    BOOST_CHECK_EQUAL(shape->GetArea(), 0.0);
}

BOOST_AUTO_TEST_CASE(factory_parse_rectangle)
{
    auto shape = CShapeParser::ParseCommand("rectangle 10 20 30 40 ff0000 00ff00");
    BOOST_REQUIRE(shape != nullptr);
    BOOST_CHECK_EQUAL(shape->GetArea(), 1200.0);
}

BOOST_AUTO_TEST_CASE(find_max_area)
{
    std::vector<std::unique_ptr<IShape>> shapes;
    shapes.push_back(std::make_unique<CRectangle>(CPoint(0, 0), 10, 10, 0, 0));
    shapes.push_back(std::make_unique<CCircle>(CPoint(0, 0), 5, 0, 0));

    auto* maxShape = FindShapeWithMaxArea(shapes);
    BOOST_REQUIRE(maxShape != nullptr);
    BOOST_CHECK(maxShape->GetArea() == 100.0);
}

BOOST_AUTO_TEST_SUITE_END()