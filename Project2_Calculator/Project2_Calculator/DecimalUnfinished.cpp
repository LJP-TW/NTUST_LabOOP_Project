#include "Decimal.h"

const bool Decimal::operator>(const Decimal& other) const
{
	return false;
}

const bool Decimal::operator>(const Integer& other) const
{
	return false;
}

const bool Decimal::operator>=(const Decimal& other) const
{
	return false;
}

const bool Decimal::operator>=(const Integer& other) const
{
	return false;
}

const bool Decimal::operator<(const Decimal& other) const
{
	return false;
}

const bool Decimal::operator<(const Integer& other) const
{
	return false;
}

const bool Decimal::operator<=(const Decimal& other) const
{
	return false;
}

const bool Decimal::operator<=(const Integer& other) const
{
	return false;
}

const bool Decimal::operator==(const Decimal& other) const
{
	return false;
}

const bool Decimal::operator==(const Integer& other) const
{
	return false;
}

const Integer Decimal::dtoi() const
{
	Integer newInteger;

	// Write some code

	return newInteger;
}

void Decimal::reduceFraction()
{
	// ¬ù¤À
}

Integer Decimal::getGCD(Integer a, Integer b) const
{
	return Integer();
}

Decimal operator+(const Integer & lva, const Decimal & rva)
{
	return Decimal();
}

Decimal operator-(const Integer & lva, const Decimal & rva)
{
	return Decimal();
}

Decimal operator*(const Integer & lva, const Decimal & rva)
{
	return Decimal();
}

Decimal operator/(const Integer & lva, const Decimal & rva)
{
	return Decimal();
}
