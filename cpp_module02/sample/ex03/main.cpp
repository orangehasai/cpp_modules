#include "Point.hpp"

#include <iostream>

static void printResult(const char *label, Point const &a, Point const &b,
	Point const &c, Point const &point)
{
	std::cout << label << ": " << bsp(a, b, c, point) << std::endl;
}

int main(void)
{
	Point const a(0.0f, 0.0f);
	Point const b(10.0f, 0.0f);
	Point const c(2.5f, 7.5f);
	Point const inside(3.0f, 2.0f);
	Point const outside(9.0f, 7.0f);
	Point const edge(5.0f, 0.0f);
	Point const vertex(0.0f, 0.0f);
	Point const almostEdge(5.0f, 0.01f);
	Point const d1(1.0f, 1.0f);
	Point const d2(2.0f, 2.0f);
	Point const d3(3.0f, 3.0f);

	printResult("inside", a, b, c, inside);
	printResult("outside", a, b, c, outside);
	printResult("edge", a, b, c, edge);
	printResult("vertex", a, b, c, vertex);
	printResult("almost edge", a, b, c, almostEdge);
	printResult("degenerate triangle", d1, d2, d3, inside);

	return 0;
}
