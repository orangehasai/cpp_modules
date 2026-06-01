#include "Fixed.hpp"

#include <cmath>
#include <ostream>

Fixed::Fixed() : _rawBits(0)
{
}

Fixed::Fixed(const int value) : _rawBits(value << _fractionalBits)
{
}

Fixed::Fixed(const float value)
	: _rawBits(static_cast<int>(roundf(value * (1 << _fractionalBits))))
{
}

Fixed::Fixed(const Fixed &other) : _rawBits(other._rawBits)
{
}

Fixed &Fixed::operator=(const Fixed &other)
{
	if (this != &other)
	{
		_rawBits = other._rawBits;
	}
	return *this;
}

Fixed::~Fixed()
{
}

int Fixed::getRawBits(void) const
{
	return _rawBits;
}

void Fixed::setRawBits(int const raw)
{
	_rawBits = raw;
}

float Fixed::toFloat(void) const
{
	return static_cast<float>(_rawBits) / static_cast<float>(1 << _fractionalBits);
}

int Fixed::toInt(void) const
{
	return _rawBits / (1 << _fractionalBits);
}

bool Fixed::operator>(const Fixed &other) const
{
	return _rawBits > other._rawBits;
}

bool Fixed::operator<(const Fixed &other) const
{
	return _rawBits < other._rawBits;
}

bool Fixed::operator>=(const Fixed &other) const
{
	return _rawBits >= other._rawBits;
}

bool Fixed::operator<=(const Fixed &other) const
{
	return _rawBits <= other._rawBits;
}

bool Fixed::operator==(const Fixed &other) const
{
	return _rawBits == other._rawBits;
}

bool Fixed::operator!=(const Fixed &other) const
{
	return _rawBits != other._rawBits;
}

Fixed Fixed::operator+(const Fixed &other) const
{
	Fixed result;

	result.setRawBits(_rawBits + other._rawBits);
	return result;
}

Fixed Fixed::operator-(const Fixed &other) const
{
	Fixed result;

	result.setRawBits(_rawBits - other._rawBits);
	return result;
}

Fixed Fixed::operator*(const Fixed &other) const
{
	Fixed result;
	long product;

	product = static_cast<long>(_rawBits) * static_cast<long>(other._rawBits);
	result.setRawBits(static_cast<int>(product / (1 << _fractionalBits)));
	return result;
}

Fixed Fixed::operator/(const Fixed &other) const
{
	Fixed result;
	long dividend;

	dividend = static_cast<long>(_rawBits) << _fractionalBits;
	result.setRawBits(static_cast<int>(dividend / other._rawBits));
	return result;
}

Fixed &Fixed::operator++()
{
	++_rawBits;
	return *this;
}

Fixed Fixed::operator++(int)
{
	Fixed before(*this);

	++_rawBits;
	return before;
}

Fixed &Fixed::operator--()
{
	--_rawBits;
	return *this;
}

Fixed Fixed::operator--(int)
{
	Fixed before(*this);

	--_rawBits;
	return before;
}

Fixed &Fixed::min(Fixed &lhs, Fixed &rhs)
{
	if (lhs < rhs)
	{
		return lhs;
	}
	return rhs;
}

const Fixed &Fixed::min(const Fixed &lhs, const Fixed &rhs)
{
	if (lhs < rhs)
	{
		return lhs;
	}
	return rhs;
}

Fixed &Fixed::max(Fixed &lhs, Fixed &rhs)
{
	if (lhs > rhs)
	{
		return lhs;
	}
	return rhs;
}

const Fixed &Fixed::max(const Fixed &lhs, const Fixed &rhs)
{
	if (lhs > rhs)
	{
		return lhs;
	}
	return rhs;
}

std::ostream &operator<<(std::ostream &out, const Fixed &fixed)
{
	out << fixed.toFloat();
	return out;
}
