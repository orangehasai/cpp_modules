#ifndef FIXED_HPP
#define FIXED_HPP

class Fixed
{
  public:
	Fixed();
	Fixed(const Fixed &other);
	Fixed(const int raw);
	Fixed(const float raw);
	Fixed &operator=(const Fixed &other);
	~Fixed();

	int getRawBits(void) const;
	void setRawBits(int const raw);
	float toFloat(void) const;

  private:
	int _rawBits;
	static const int fractionalBits = 8;
};

#endif
