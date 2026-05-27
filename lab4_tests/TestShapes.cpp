#include "stdafx.h"
#include "../lab4/CCircle.h"
#include "../lab4/CLineSegment.h"
#include "../lab4/CPoint.h"
#include "../lab4/CRectangle.h"
#include "../lab4/CTriangle.h"
#include "../lab4/ShapeFinder.h"
#include "../lab4/ShapeParser.h"

BOOST_AUTO_TEST_SUITE(Point)
	BOOST_AUTO_TEST_CASE(default_is_zero)
	{
		CPoint point;
		BOOST_CHECK_EQUAL(point.GetX(), 0.0);
		BOOST_CHECK_EQUAL(point.GetY(), 0.0);
	}
	BOOST_AUTO_TEST_CASE(holds_given_coordinates)
	{
		CPoint point(3.5, -2.0);
		BOOST_CHECK_EQUAL(point.GetX(), 3.5);
		BOOST_CHECK_EQUAL(point.GetY(), -2.0);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(LineSegment)
	BOOST_AUTO_TEST_CASE(perimeter_is_length)
	{
		CLineSegment line(CPoint(0, 0), CPoint(3, 4), 0x000000);
		BOOST_CHECK_EQUAL(line.GetPerimeter(), 5.0);
	}
	BOOST_AUTO_TEST_CASE(area_is_zero)
	{
		CLineSegment line(CPoint(0, 0), CPoint(10, 10), 0x000000);
		BOOST_CHECK_EQUAL(line.GetArea(), 0.0);
	}
	BOOST_AUTO_TEST_CASE(zero_length_segment)
	{
		CLineSegment line(CPoint(5, 5), CPoint(5, 5), 0x000000);
		BOOST_CHECK_EQUAL(line.GetPerimeter(), 0.0);
	}
	BOOST_AUTO_TEST_CASE(start_and_end_points)
	{
		CLineSegment line(CPoint(1, 2), CPoint(3, 4), 0x000000);
		BOOST_CHECK_EQUAL(line.GetStartPoint().GetX(), 1.0);
		BOOST_CHECK_EQUAL(line.GetEndPoint().GetY(), 4.0);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Triangle)
	BOOST_AUTO_TEST_CASE(right_triangle_area)
	{
		CTriangle triangle(CPoint(0, 0), CPoint(4, 0), CPoint(0, 3), 0, 0);
		BOOST_CHECK_EQUAL(triangle.GetArea(), 6.0);
	}
	BOOST_AUTO_TEST_CASE(degenerate_triangle_zero_area)
	{
		CTriangle triangle(CPoint(0, 0), CPoint(5, 0), CPoint(10, 0), 0, 0);
		BOOST_CHECK_EQUAL(triangle.GetArea(), 0.0);
	}
	BOOST_AUTO_TEST_CASE(vertices_correct)
	{
		CTriangle triangle(CPoint(0, 0), CPoint(4, 0), CPoint(0, 3), 0, 0);
		BOOST_CHECK_EQUAL(triangle.GetVertex1().GetX(), 0.0);
		BOOST_CHECK_EQUAL(triangle.GetVertex2().GetX(), 4.0);
		BOOST_CHECK_EQUAL(triangle.GetVertex3().GetY(), 3.0);
	}
	BOOST_AUTO_TEST_CASE(colors_correct)
	{
		CTriangle triangle(CPoint(0, 0), CPoint(1, 0), CPoint(0, 1), 0x123456, 0xABCDEF);
		BOOST_CHECK_EQUAL(triangle.GetOutlineColor(), 0x123456);
		BOOST_CHECK_EQUAL(triangle.GetFillColor(), 0xABCDEF);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Rectangle)
	BOOST_AUTO_TEST_CASE(area_and_perimeter)
	{
		CRectangle rect(CPoint(0, 10), 5, 10, 0, 0);
		BOOST_CHECK_EQUAL(rect.GetArea(), 50.0);
		BOOST_CHECK_EQUAL(rect.GetPerimeter(), 30.0);
	}
	BOOST_AUTO_TEST_CASE(zero_dimensions)
	{
		CRectangle rect(CPoint(0, 0), 0, 0, 0, 0);
		BOOST_CHECK_EQUAL(rect.GetArea(), 0.0);
		BOOST_CHECK_EQUAL(rect.GetPerimeter(), 0.0);
	}
	BOOST_AUTO_TEST_CASE(right_bottom_corner)
	{
		CRectangle rect(CPoint(10, 20), 30, 40, 0, 0);
		CPoint rightBottom = rect.GetRightBottom();
		BOOST_CHECK_EQUAL(rightBottom.GetX(), 40.0);
		BOOST_CHECK_EQUAL(rightBottom.GetY(), -20.0);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Circle)
	BOOST_AUTO_TEST_CASE(area_and_perimeter)
	{
		CCircle circle(CPoint(0, 0), 5, 0, 0);
		BOOST_CHECK_CLOSE(circle.GetArea(), 78.5398, 0.01);
		BOOST_CHECK_CLOSE(circle.GetPerimeter(), 31.4159, 0.01);
	}
	BOOST_AUTO_TEST_CASE(zero_radius)
	{
		CCircle circle(CPoint(10, 20), 0, 0, 0);
		BOOST_CHECK_EQUAL(circle.GetArea(), 0.0);
		BOOST_CHECK_EQUAL(circle.GetPerimeter(), 0.0);
	}
	BOOST_AUTO_TEST_CASE(center_and_radius)
	{
		CCircle circle(CPoint(3.5, -2.0), 7.5, 0, 0);
		BOOST_CHECK_EQUAL(circle.GetCenter().GetX(), 3.5);
		BOOST_CHECK_EQUAL(circle.GetRadius(), 7.5);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(ShapeParser)
	BOOST_AUTO_TEST_CASE(parse_line)
	{
		auto shape = CShapeParser::ParseCommand("line 0 0 3 4 000000");
		BOOST_REQUIRE(shape != nullptr);
		BOOST_CHECK_EQUAL(shape->GetPerimeter(), 5.0);
	}
	BOOST_AUTO_TEST_CASE(parse_triangle)
	{
		auto shape = CShapeParser::ParseCommand("triangle 0 0 4 0 0 3 ff0000 00ff00");
		BOOST_REQUIRE(shape != nullptr);
		BOOST_CHECK_EQUAL(shape->GetArea(), 6.0);
	}
	BOOST_AUTO_TEST_CASE(parse_rectangle)
	{
		auto shape = CShapeParser::ParseCommand("rectangle 10 20 30 40 ff0000 00ff00");
		BOOST_REQUIRE(shape != nullptr);
		BOOST_CHECK_EQUAL(shape->GetArea(), 1200.0);
	}
	BOOST_AUTO_TEST_CASE(parse_circle)
	{
		auto shape = CShapeParser::ParseCommand("circle 0 0 5 ff0000 00ff00");
		BOOST_REQUIRE(shape != nullptr);
		BOOST_CHECK(shape->GetArea() > 0.0);
	}
	BOOST_AUTO_TEST_CASE(empty_string_returns_null)
	{
		BOOST_CHECK(CShapeParser::ParseCommand("") == nullptr);
	}
	BOOST_AUTO_TEST_CASE(unknown_shape_returns_null)
	{
		BOOST_CHECK(CShapeParser::ParseCommand("pentagon 0 0 5 ff0000 00ff00") == nullptr);
	}
	BOOST_AUTO_TEST_CASE(missing_arguments_circle_returns_null)
	{
		BOOST_CHECK(CShapeParser::ParseCommand("circle") == nullptr);
		BOOST_CHECK(CShapeParser::ParseCommand("circle 0 0 5 ff0000") == nullptr);
	}
	BOOST_AUTO_TEST_CASE(missing_arguments_line_returns_null)
	{
		BOOST_CHECK(CShapeParser::ParseCommand("line 0 0 3 ff0000") == nullptr);
	}
	BOOST_AUTO_TEST_CASE(missing_arguments_triangle_returns_null)
	{
		BOOST_CHECK(CShapeParser::ParseCommand("triangle 0 0 4 0 0 ff0000 00ff00") == nullptr);
	}
	BOOST_AUTO_TEST_CASE(missing_arguments_rectangle_returns_null)
	{
		BOOST_CHECK(CShapeParser::ParseCommand("rectangle 10 20 30 ff0000 00ff00") == nullptr);
	}
	BOOST_AUTO_TEST_CASE(non_numeric_coordinates_returns_null)
	{
		BOOST_CHECK(CShapeParser::ParseCommand("circle abc 0 5 ff0000 00ff00") == nullptr);
	}
	BOOST_AUTO_TEST_CASE(negative_coordinates_are_valid)
	{
		auto shape = CShapeParser::ParseCommand("line -1 -2 -4 -6 000000");
		BOOST_REQUIRE(shape != nullptr);
		BOOST_CHECK_EQUAL(shape->GetPerimeter(), 5.0);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(ShapeFinder)
	BOOST_AUTO_TEST_CASE(find_max_area)
	{
		std::vector<std::unique_ptr<IShape>> shapes;
		shapes.push_back(std::make_unique<CRectangle>(CPoint(0, 0), 10, 10, 0, 0));
		shapes.push_back(std::make_unique<CCircle>(CPoint(0, 0), 5, 0, 0));
		auto* maxShape = FindShapeWithMaxArea(shapes);
		BOOST_REQUIRE(maxShape != nullptr);
		BOOST_CHECK_EQUAL(maxShape->GetArea(), 100.0);
	}
	BOOST_AUTO_TEST_CASE(find_min_perimeter)
	{
		std::vector<std::unique_ptr<IShape>> shapes;
		shapes.push_back(std::make_unique<CRectangle>(CPoint(0, 0), 10, 10, 0, 0));
		shapes.push_back(std::make_unique<CLineSegment>(CPoint(0, 0), CPoint(3, 4), 0));
		auto* minShape = FindShapeWithMinPerimeter(shapes);
		BOOST_REQUIRE(minShape != nullptr);
		BOOST_CHECK_EQUAL(minShape->GetPerimeter(), 5.0);
	}
	BOOST_AUTO_TEST_CASE(empty_vector_returns_null)
	{
		std::vector<std::unique_ptr<IShape>> shapes;
		BOOST_CHECK(FindShapeWithMaxArea(shapes) == nullptr);
		BOOST_CHECK(FindShapeWithMinPerimeter(shapes) == nullptr);
	}
BOOST_AUTO_TEST_SUITE_END()
