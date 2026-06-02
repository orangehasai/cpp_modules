#include <iostream>
#include <cmath>

#include "Fixed.hpp"

Fixed::Fixed() : _rawBits(0)
{
}

Fixed::Fixed(const int value) : _rawBits(value << _fractionalBits)
{
}

Fixed::Fixed(const float value) : _rawBits(static_cast<int>(roundf(value * (1 << _fractionalBits))))
{
}

Fixed::Fixed(const Fixed &other)
{
	*this = other;
}

Fixed &Fixed::operator=(const Fixed &other)
{
	if (this != &other)
	{
		this->_rawBits = other._rawBits;
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
	return this->_rawBits > other._rawBits;
}

bool Fixed::operator<(const Fixed &other) const
{
	return this->_rawBits < other._rawBits;
}

bool Fixed::operator>=(const Fixed &other) const
{
	return this->_rawBits >= other._rawBits;
}

bool Fixed::operator<=(const Fixed &other) const
{
	return this->_rawBits <= other._rawBits;
}

bool Fixed::operator==(const Fixed &other) const
{
	return this->_rawBits == other._rawBits;
}

bool Fixed::operator!=(const Fixed &other) const
{
	return this->_rawBits != other._rawBits;
}

Fixed Fixed::operator+(const Fixed &other) const
{
	Fixed result;

	result.setRawBits(this->_rawBits + other._rawBits);
	return result;
}

Fixed Fixed::operator-(const Fixed &other) const
{
	Fixed result;

	result.setRawBits(this->_rawBits - other._rawBits);
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
	++this->_rawBits;
	return *this;
}

Fixed &Fixed::operator--()
{
	--this->_rawBits;
	return *this;
}

Fixed Fixed::operator++(int)
{
	Fixed old(*this);

	++this->_rawBits;
	return old;
}

Fixed Fixed::operator--(int)
{
	Fixed old(*this);

	--this->_rawBits;
	return old;
}

Fixed &Fixed::min(Fixed &f1, Fixed &f2)
{
	if (f1._rawBits < f2._rawBits)
		return f1;
	return f2;
}
const Fixed &Fixed::min(const Fixed &f1, const Fixed &f2)
{
	if (f1._rawBits < f2._rawBits)
		return f1;
	return f2;
}
Fixed &Fixed::max(Fixed &f1, Fixed &f2)
{
	if (f1._rawBits > f2._rawBits)
		return f1;
	return f2;
}
const Fixed &Fixed::max(const Fixed &f1, const Fixed &f2)
{
	if (f1._rawBits > f2._rawBits)
		return f1;
	return f2;
}

std::ostream &operator<<(std::ostream &out, const Fixed &fixed)
{
	out << fixed.toFloat();
	return out;
}
