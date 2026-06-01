#include "Fixed.hpp"

#include <iostream>

static void printComparisons(const Fixed &lhs, const Fixed &rhs)
{
	std::cout << lhs << " > " << rhs << " : " << (lhs > rhs) << std::endl;
	std::cout << lhs << " < " << rhs << " : " << (lhs < rhs) << std::endl;
	std::cout << lhs << " >= " << rhs << " : " << (lhs >= rhs) << std::endl;
	std::cout << lhs << " <= " << rhs << " : " << (lhs <= rhs) << std::endl;
	std::cout << lhs << " == " << rhs << " : " << (lhs == rhs) << std::endl;
	std::cout << lhs << " != " << rhs << " : " << (lhs != rhs) << std::endl;
}

static void printArithmetic(const Fixed &lhs, const Fixed &rhs)
{
	std::cout << lhs << " + " << rhs << " = " << (lhs + rhs) << std::endl;
	std::cout << lhs << " - " << rhs << " = " << (lhs - rhs) << std::endl;
	std::cout << lhs << " * " << rhs << " = " << (lhs * rhs) << std::endl;
	std::cout << lhs << " / " << rhs << " = " << (lhs / rhs) << std::endl;
}

int main(void)
{
	std::cout << "Subject sample:" << std::endl;
	Fixed a;
	Fixed const b(Fixed(5.05f) * Fixed(2));

	std::cout << a << std::endl;
	std::cout << ++a << std::endl;
	std::cout << a << std::endl;
	std::cout << a++ << std::endl;
	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << Fixed::max(a, b) << std::endl;

	std::cout << std::endl;
	std::cout << "More operator checks:" << std::endl;
	Fixed x(3.5f);
	Fixed y(2);
	Fixed counter;
	Fixed const cx(-1.25f);
	Fixed const cy(0.75f);

	printComparisons(x, y);
	std::cout << std::endl;
	printArithmetic(x, y);
	std::cout << std::endl;
	std::cout << "counter      = " << counter << std::endl;
	std::cout << "counter++    = " << counter++ << std::endl;
	std::cout << "after ++     = " << counter << std::endl;
	std::cout << "--counter    = " << --counter << std::endl;
	std::cout << "min(x, y)    = " << Fixed::min(x, y) << std::endl;
	std::cout << "max(x, y)    = " << Fixed::max(x, y) << std::endl;
	std::cout << "min(cx, cy)  = " << Fixed::min(cx, cy) << std::endl;
	std::cout << "max(cx, cy)  = " << Fixed::max(cx, cy) << std::endl;

	return 0;
}
