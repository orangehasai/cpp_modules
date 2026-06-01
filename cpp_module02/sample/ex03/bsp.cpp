#include "Point.hpp"

static Fixed signedArea(Point const &a, Point const &b, Point const &c)
{
	return (b.getX() - a.getX()) * (c.getY() - a.getY())
		- (b.getY() - a.getY()) * (c.getX() - a.getX());
}

bool bsp(Point const a, Point const b, Point const c, Point const point)
{
	Fixed const zero(0);
	Fixed const triangleArea = signedArea(a, b, c);
	Fixed const abp = signedArea(a, b, point);
	Fixed const bcp = signedArea(b, c, point);
	Fixed const cap = signedArea(c, a, point);
	bool const hasNegative = (abp < zero) || (bcp < zero) || (cap < zero);
	bool const hasPositive = (abp > zero) || (bcp > zero) || (cap > zero);

	if (triangleArea == zero)
	{
		return false;
	}
	if (abp == zero || bcp == zero || cap == zero)
	{
		return false;
	}
	return !(hasNegative && hasPositive);
}
